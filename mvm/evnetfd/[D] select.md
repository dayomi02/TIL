# Select

select는 싱글쓰레드(하나의 쓰레드로 동작)로 다중 I/O를 처리하는 멀티플렉싱(하나의 통신 채널을 통해서 둘 이상의 데이터를 전송) 통지 모델의 가장 대표적인 방법이다. 해당 fd가 I/O를 할 준비가 되었는지 알 수 있다면, 그 fd가 할당받은 버퍼에 데이터를 복사해주기만 하면 된다. 이런 작업을 하기 위해서는 fd의 상황을 파악할 수 있는 기능을 가지고 있어야 한다. select는 많은 fd들을 한까반에 관찰하는 FD_SET 구조체를 사용하여 빠르고 간편하게 유저에게 fd의 상황을 알려준다.

<br>

### FD_SET - 구조체

FD_SET은 하나의 fd의 상태를 하나의 비트로 표현한다.

fd의 번호를 FD_SET에 등록하면 해당 배트의 값이 1로 저장된다. 그리고 I/O처리 준비가 되면 select를 통해 해당 비트의 값을 갱신하고 프로세스는 변경된 값을 보고 버퍼에 데이터를 복사한다.

비트연산을 단순화하여 여러 매크로를 제공한다. →FD_ZERO, FD_SET, FD_CLR, FD_ISSET

<br>

### select

select는 read/write/error 3가지 I/O에 대한 통지를 받는다.

관찰 범위 내의 fd값에서 I/O에 대한 통지가 날라오는 것을 감지하는(?)역할을 한다.

fd의 범위를 지정해 주고 일정 시간이나 변화가 있을 때까지 I/O를 감지하는 역할을 한다.

```c
int select( int maxfdNum, //파일 디스크립터의 관찰 범위 (0 ~ maxfdNum -1)
            fd_set *restrict readfds, //read I/O를 통지받을 FD_SET의 주소, 없으면 NULL
            fd_set *restrict writefds,//write I/O를 통지받을 FD_SET의 주소, 없으면 NULL
            fd_set *restrict errorfds,//error I/O를 통지받을 FD_SET의 주소, 없으면 NULL
            struct timeval *restrict timeout //null이면 변화가 있을 때까지 계속 Block, 
                                             //아니면 주어진 시간만큼 대기후 timeout.
           );
//반환값 : 오류 발생시 -1, timeout에 의한 반환은 0, 정상 작동일때 변경된 파일 디스크립터 개수
```

fd의 개수가 최대 1024개로 제한된다.

select가 모든 fd를 순회하면서 FD_ISSET으로 체크하는 작업이 불필요해 보인다.

→ 실제로 상태가 변화된 fd의 목록만 넘겨준다면 보다 더 빠르게 동작할 수 있지 않을까?

fd에 대한 정보인 구조체 FD_SET을 계속해서 select를 이용해 운영체제에게 전달하는 것이 부하를 일으킬 수 있다.

→ FD_SET을 만들었을 때, I/O 처리가 발생할 경우에만 운영체제에게 데이터를 전달하면 어떨까?

select를 사용해서 I/O의 상황을 알기 위해서는 프로세스가 커널에게 직접 상황 체크를 요청해야한다. 프로세스와 커널이 서로 동기화 되어있다고 볼 수 있다. (select의 통지 형태는 동기형 통지 방식이다.)





