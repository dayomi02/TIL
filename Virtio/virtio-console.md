https://projectacrn.github.io/latest/developer-guides/hld/virtio-console.html
<br>


## Virtio-console ?

Virtio-console은 데이터 입력 및 출력을 위한 간단한 장치이다. console의 virtio device ID는 3이며 1~16개의 포트를 가질 수 있다. 각 포트에는 FE(Front End) 드라이버와 BE(Back End) 드라이버 간의 정보 통신에 사용되는 **입력 및 출력 virtqueue**가 있다. 현재 각 virtqueue의 크기는 64(소스 코드에서 구성 가능)이다. FE 드라이버는 수신 되는 데이터에 대한 빈 버퍼를 receiving virtqueue에 배치하고, 송신 문자를 transmirring virtqueue에 추가 시킨다.

Virtio-console device는 Control IO virtqueue도 있다. Control virtqueue는 디바이스와 드라이버 간에 정보를 전달하는 데 사용된다. 
including : 연결의 양쪽에서 열리고 닫히는 포트, Host에서 특정 포트가 콘솔 포트인지 여부에 대한 표시, 새 포트 추가, 포트 hot-plug 또는 unplug, 포트 또는 디바이스가 성공적으로 추가되었는지 또는 포트가 열렸는지 또는 닫혔는지 여부를 게스트에서 알려줌 

virtio-console architecture diagram

Virtio-console은 ACRN Device Model(DM)에서 virtio legacy device로 구현되며, guest OS에 PCI virtio device로 등록된다. guest Kernel(User VM)을 `CONFIG_VIRTIO_CONSOLE=y` 로 빌드해야 하는 경우를 제외하고  frontend Linux virtio-console에서는 변경할 필요가 없다.

포트가 콘솔로 구성된 경우 Virtio-console FE driver는 HVC console을 커널에 등록한다. 그렇지 않으면 커널에 `/dev/vportXpY`라는 이름의 char device를 등록하고 사용자 공간에서 읽고 쓸 수 있다.
포트에는 두 가지 virtqueue가 있는데 하나는 수신용이고 하나는 송신용이다. FE driver는 빈 버퍼를 수신 데이터의 receiving virtqueue에 배치하고 송신 문자를 transmirring virtqueue에 추가 시킨다.

Virtio-console BE driver는 virtqueue에서 kick를 받으면  FE의 transmitting virtqueue(송신)로부터 데이터를 복사한다. 그런 다음 BE driver는 데이터를 백엔드에 기록하고 PTY, TTY, STDIO 및 일반 파일로 구현할 수 있다. BE driver는 mevent를 사용하여 백엔드 파일 설명자에서 사용 가능한 데이터를 폴링한다. 새로운 데이터를 사용할 수 있을 때, BE driver는 새로운 데이터를 FE의 receiving virtqueue(수신)로 읽고, 이어서 인터럽트를 발생시킨다.

Virtio-console은 guest 출력을 다양한 백엔드 디바이스로 리다이렉션(다시 보냄) 할 수 있도록 지원한다. 현재 ACRN device model에서는 STDIO, TTY,PTY 및 일반 file이 지원된다.

## Console Backend Use Cases

### STDIO

```c
/* device model(acrn-md) command line */
-s n,virtio-console,@**stdio**:stdio_port

/* guest OS kernel command line */
console=hvc0
```

```c
/* static int virtio_console_open_backend(const char *path,
			    enum virtio_console_be_type be_type) */

case VIRTIO_CONSOLE_BE_STDIO:
		if (stdio_in_use) {
			WPRINTF(("vtcon: stdio is used by other device\n"));
			break;
		}
		fd = STDIN_FILENO;
		stdio_in_use = true;
		break;
```

**VIRTIO_CONSOLE_BE_STDIO** - 인자로 받은 be_type값에 따라서 case문 실행 

- stdio_in_use를 확인해서 stdio가 사용 중인지 확인
- fd 값을 STDIN_FILENO으로 설정 (Standard input)
- stdio_in_use값을 true로 변경해 stdio를 사용하고 있다고 나타냄

```c
sudo acrn-dm -A -m 1024M -s 0:0,hostbridge \
-s 3,virtio-blk,/home/dayeon/acrn-dm-bins/UOS.img \
-s 4,virtio-net,tap0 \
-s 5,virtio-console,@stdio:stdio_port \
-k /home/dayeon/acrn-dm-bins/bzImage_uos \
-B "earlyprintk=serial,ttyS0,115200n8 consoleblank=0 root=/dev/vda1 rw rootwait maxcpus=1 nohpet console=tty0 console=hvc0 console=ttyS0 no_timer_check ignore_loglevel log_buf_len=16M tsc=reliable" \
$logger_setting \
ubuntu_vm
```

### PTY

PTY (Pseudo-Terminal) : 가상 터미널 환경

```c
/* device model(acrn-md) command line */
-s n,virtio-console,@**pty**:pty_port

/* guest OS kernel command line */
console=hvc0

/* Use a terminal emulator, to connect to the TTY node*/
# minicom -D /dev/pts/0
# screen /dev/pts/0
```

```c
/* static int virtio_console_open_backend(const char *path,
			    enum virtio_console_be_type be_type) */

case VIRTIO_CONSOLE_BE_PTY:
		fd = posix_openpt(O_RDWR | O_NOCTTY);
		if (fd == -1)
			WPRINTF(("vtcon: posix_openpt failed, errno = %d\n",
				errno));
		else if (grantpt(fd) == -1 || unlockpt(fd) == -1) {
			WPRINTF(("vtcon: grant/unlock failed, errno = %d\n",
				errno));
			close(fd);
			fd = -1;
		}
		break;
```

**VIRTIO_CONSOLE_BE_PTY** - 인자로 받은 be_type값에 따라서 case문 실행 

- posix_openpt()함수 호출
PTY에 대한 master device와 file descriptor 사이의 연결을 설정하는 함수
- grantpt()함수, unlockpt()함수 호출
slave PTY device에 대한 액세스 권한 부여하는 함수(완료 시 0 반환)
PTY master/slave 쌍 Unlock(완료 시 0 반환)

```c
sudo acrn-dm -A -m 1024M -s 0:0,hostbridge \
-s 3,virtio-blk,/home/dayeon/acrn-dm-bins/UOS.img \
-s 4,virtio-net,tap0 \
-s 5,virtio-console,@**pty**:pty_port \
-k /home/dayeon/acrn-dm-bins/bzImage_uos \
-B "earlyprintk=serial,ttyS0,115200n8 consoleblank=0 root=/dev/vda1 rw rootwait maxcpus=1 nohpet console=tty0 console=hvc0 console=ttyS0 no_timer_check ignore_loglevel log_buf_len=16M tsc=reliable" \
$logger_setting \
ubuntu_vm
```

### TTY

TTY (Tele Type Writer) : 콘솔 및 터미널 환경

```c
/* device model(acrn-md) command line */
-s n,virtio-console,@tty:tty_port=/dev/pts/X

/* guest OS kernel command line */
console=hvc0
```

```c
/* static int virtio_console_open_backend(const char *path,
			    enum virtio_console_be_type be_type) */

case VIRTIO_CONSOLE_BE_TTY:
		fd = open(path, O_RDWR | O_NONBLOCK);
		if (fd < 0)
			WPRINTF(("vtcon: open failed: %s\n", path));
		else if (!isatty(fd)) {
			WPRINTF(("vtcon: not a tty: %s\n", path));
			close(fd);
			fd = -1;
		}
		break;
```

- open()함수를 사용해서 path의 파일 오픈, fd값 반환
- fd값이 0보다 작은지 확인 (파일 열기에 실패했는지)
- fd값이 터미널 디바이스인지 확인 (tty인지)

```c
sudo acrn-dm -A -m 1024M -s 0:0,hostbridge \
-s 3,virtio-blk,/home/dayeon/acrn-dm-bins/UOS.img \
-s 4,virtio-net,tap0 \
-s 5,virtio-console,@tty:tty_port=/dev/pts/X \
-k /home/dayeon/acrn-dm-bins/bzImage_uos \
-B "earlyprintk=serial,ttyS0,115200n8 consoleblank=0 root=/dev/vda1 rw rootwait maxcpus=1 nohpet console=tty0 console=hvc0 console=ttyS0 no_timer_check ignore_loglevel log_buf_len=16M tsc=reliable" \
$logger_setting \
ubuntu_vm
```

### FILE

```c
/* device model(acrn-md) command line */
-s n,virtio-console,@file:file_port=</path/to/file>

/* guest OS kernel command line */
console=hvc0
```

```c
/* static int virtio_console_open_backend(const char *path,
			    enum virtio_console_be_type be_type) */

case VIRTIO_CONSOLE_BE_FILE:
		fd = open(path, O_WRONLY|O_CREAT|O_APPEND|O_NONBLOCK, 0666);
		if (fd < 0)
			WPRINTF(("vtcon: open failed: %s\n", path));
		break;
```

- open()함수로 path의 파일을 오픈
- fd값이 0보다 작은지 확인 (파일 열기에 실패했는지)

```c
sudo acrn-dm -A -m 1024M -s 0:0,hostbridge \
-s 3,virtio-blk,/home/dayeon/acrn-dm-bins/UOS.img \
-s 4,virtio-net,tap0 \
-s 5,virtio-console,@file:file_port=/dev/pts/X \
-k /home/dayeon/acrn-dm-bins/bzImage_uos \
-B "earlyprintk=serial,ttyS0,115200n8 consoleblank=0 root=/dev/vda1 rw rootwait maxcpus=1 nohpet console=tty0 console=hvc0 console=ttyS0 no_timer_check ignore_loglevel log_buf_len=16M tsc=reliable" \
$logger_setting \
ubuntu_vm
```
