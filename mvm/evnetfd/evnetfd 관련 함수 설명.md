## evnetfd관련 함수 설명
<br>

### Function - eventfd()

eventfd는 리눅스기반 운영체제에서 파일 디스크립터를 통해 프로세스들끼리 통신할 수 있는 API중 하나이다. 데이터 전송보다는 프로세스간에 event를 전달하는 용도로 사용한다.

```c
#include <sys/eventfd.h>

int eventfd (unsigned initval, int flag)
```

프로세스들끼리 통신할 수 있는 파일 디스크립터를 만드는 함수이다. 종료 후에는 채널로 사용할 수 있는 64bit 정수형 파일 디스크립터가 반환된다.

[eventfd(2) - Linux manual page](https://man7.org/linux/man-pages/man2/eventfd.2.html)
> evnetfd() 함수 설명

<br>


### Function - read()

```c
ssize_t read (int fd, void *buf, size_t nbytes)
```

파일 읽기. 파일의 데이터를 입력받는 함수

fd : 파일 디스크립터

buf : 파일을 읽어 들일 버퍼, 수신한 데이터를 저장할 버퍼를 가리키는 포인터

nbytes : 버퍼의 크기, 수신할 최대 바이트 수

정상적으로 실행되었다면 읽어들인 바이트 수를 반환하고, 실패했다면 -1을 반환한다.

<br>


### Function - write()

```c
ssize_t write (int df, const void *buf, size_t nbytes);
```

파일 쓰기. 파일에 데이터를 출력하는 함수

fd : 파일 디스크립터

buf : 전송할 데이터를 가지고 있는 버퍼의 포인터

nbytes : 전송할 최대 바이트 수

정상적으로 실행되었다면 전달한 바이트 수를 반환하고, 실패했다면 -1을 반환한다.

⇒ 리눅스에서는 파일과 소캣을 동일하게 취급하므로 소캣을 통해서 호스트에게 데이터를 전송 할 때에도 이 함수를 사용함

[파일 쓰기 - write()](https://mintnlatte.tistory.com/286?category=465233)

> read(), write() 함수 설명

<br>


### Function - fork()

프로세스를 생성하고자 할 때 사용하는 함수이다.

fork함수를 호출하는 프로세스는 부모 프로세스가 되고 새롭게 생성되는 프로세스는 자식 프로세스가 된다.

fork함수에 의해 생성된 자식 프로세스는 부모 프로세스의 메모리를 그대로 복사하여 가지게 된다.

unistd.h 파일을 include해서 사용 가능하다.

성공할 경우 부모 프로세스에서는 자식 프로세스의 PID값을 반환 받고 자식 프로세스에서는 0을 반환 받음

실패할 경우 -1 반환.
