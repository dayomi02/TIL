# epoll

epoll은 확장 가능한 I/O 이벤트 알림을 위한 Linux 커널 시스템 호출이다. epoll의 기능은 여러 파일 설명자를 모니터링하여 I/O가 가능한지 여부를 확인하는 것이다.

epoll은 **select의 단점을 보완하여 리눅스 환경에서 사용할 수 있도록 만든 I/O 통지 기법**이다. 전체 fd에 대한 반복문을 사용하지 않고, select 같은 함수를 호출할 때마다 전체 관찰 대상에 대한 정보를 넘기지도 않는다.

관찰 대상인 fd들의 정보를 담은 저장소를 운영체제가 직접 담당한다. 운영체제에게 관찰 대상의 저장소를 만들어달라고 요청하면 그 저장소에 해당하는 fd (epoll_fd)를 리턴해준다. 관찰 영역이 변경되거나 변경사항을 체크할 경우에도 epoll_fd를 사용한다.

<br>

### Polling

폴링이란 하나의 장치(또는 프로그램)가 충돌 회피 또는 동기화 처리 등을 목적으로 다른 장치(또는 프로그램)의 상태를 주기적으로 검사하여 일정한 조건을 만족할 때 송수신 등의 자료처리를 하는 방식을 말한다.

epoll_fd를 만들어 주는 epoll_create()함수.

이 함수는 이벤트를 저장하기 위한 "size"만큼의 공간을 커널에 요청하는 작업을 수행한다.

수행 후 fd의 값을 반환하는데, 더이상 사용하지 않을 거라면 close함수로 닫아주면 된다.

```c
int epoll_create(int size); //size는 epoll_fd의 크기정보를 전달한다.
														//반환 값 : 실패 시 -1, 일반적으로 epoll_fd의 값을 리턴
```

관찰 대상이 되는 fd를 등록, 삭제하는데 사용되는 epoll_ctl (fd를 제어)

epoll을 제어하기 위해서 사용한다.

```c
	int epoll_ctl(int epoll_fd,           //epoll_fd
              int operate_enum,         //어떤 변경을 할지 결정하는 enum값
              int enroll_fd,            //등록할 fd
              struct epoll_event* event //관찰 대상의 관찰 이벤트 유형
              ); 
//반환 값 : 실패 시 -1, 성공시 0
```

operate_enum값은 EPOLL_CTL_ADD(새로운 fd 등록), EPOLL_CTL_DEL(기존 fd 삭제), EPOLL_CTL_MOD(등록된 fd의 이벤트 의 멤버값을 변경)로 구성된다.

```c
struct epoll_event
{
  __uint32_t events;     //발생된 이벤트
  epoll_data_t data;
}

typedef epoll_data
{
   void* ptr;
   int fd;
   __uint32_t u32;
   __uint64_t u64;
}epoll_data_t;

enum Events
{
   EPOLLIN,   //입력 이벤트 감지
   EPOLLOUT,  //출력 이벤트 감지
   EPOLLPRI,  //중요한 데이터(OOB)가 발생.
   EPOLLRDHUD,//Hang up발생 검사
   EPOLLERR,  //에러 발생
   EPOLLET,   //fd에 에러가 발생했는지 검사
   EPOLLONESHOT, //한번만 이벤트 받음
}
```

epoll_event는 fd와 event, 기타 정보를 묶어서 만든 구조체이다.

epoll_wait()는 이벤트가 발생한 fd들의 집합을 요청하는 함수이다. select와 같은 역할을 한다.

실제 이벤트가 발생하기를 기다리고 있다가, 이벤트가 발생하면 이벤트 관련 정보를 넘겨주는 역할을 한다.

```c
int epoll_wait( int epoll_fd,              //epoll_fd
                struct epoll_event* event, //event 버퍼의 주소(event관련 정보)
                int maxevents,             //버퍼에 들어갈 수 있는 구조체 최대 개수
                int timeout                //0보다 작다면 이벤트가 발생할 때까지 기다리고, 
																					 //0이면 바로 리턴, 
																					 //0보다 크면 timeout 밀리세컨드 만큼 기다림.
              );
//성공시 이벤트 발생한 파일 디스크립터 개수 반환, 실패시 -1 반환
```

이벤트가 발생할 경우 발생한 이벤트의 갯수를 반환한다.

함수가 정상 봔환될 경우 두번째 인자로 사용하는 포인터는 이벤트 발생한 fd와 이벤트의 종류가 묶여져있는 배열로 사용된다.

→ 모든 fd에 대하여 순화하면서 체크할 필요가 없다.

이벤트가 있는 fd들이 담겨오고 그 개수를 알 수 있으므로 꼭 필요한 event만 순회하면서 처리할 수 있다는 장점을 보여준다.

<br>

### epoll 실제 사용

```c
int epoll_fd = epoll_create(EPOLL_SIZE); 
struct epoll_event* events = malloc(sizeof(struct epoll_event)*EPOLL_SIZE); 
struct epoll_event init_event; 
init_event.events = EPOLLIN; 
init_event.data.fd = server_socket; 
epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_socket, &init_event); 

while(TRUE) { 
	int event_count = epoll_wait(epoll_fd, events, EPOLL_SIZE, -1); 
	if( event_count = -1 ) 
			break; 
	for( int i = 0 ; i < event_count; ++i ) 
	{ 
			if(events[i].data.fd == server_socket) //서버 소켓에 이벤트 
			{ 
						//accept 처리 
						... 
						init_event.events = EPOLLIN; 
						init_event.data.fd = new_client_socket; 
						epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_client_socket, &init_event); 
			} 
			else //이벤트가 도착한 소켓들 
			{ 
					//read, write, closesocket처리 
			} 
	} 
} 
closesocket(server_socket); 
close(epoll_fd); 
return 0;
```

epoll은 select의 단점을 많이 개선한 형태의 통지방식이다. FD_SET을 운영체제가 직접 관리하는 것으로 많은 부분이 개선되었다. 하지만 그 본질적인 동작 구조는 select와 크게 다르지 않다. 프로세스가 커널에게 지속적으로 I/O 상황을 체크하여 동기화 하는 개념은 여전히 유효하다. 따라서 epoll의 통지 모델 역시 동기형 통지 모델이다.

그리고 timeout개념이 select와 동일한 방식으로 동작한다. epoll의 전체적인 개념모델은 select와 같다고 생각한다.
