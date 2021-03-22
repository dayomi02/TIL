## eventfd.c 코드 분석
<br>

```c
#define handle_error(msg) \\
   do { perror(msg); exit(EXIT_FAILURE); } while (0)
```

\#define으로 handle_error(msg) 형식의 함수를 정의함.

오류 메시지를 출력하고 프로그램을 강제종료하는 코드를 무한반복함.

perror() :  오류 메시지 출력 함수

exit() : 종료 방식을 알려줌 (EXIT_SUCCESS,0→정상 종료)(EXIT_FAILURE,1→에러 메시지 종료)

```c
int main(int argc, char *argv[])
{
   int efd, j;
   uint64_t u;
   ssize_t s;
```

argc는 매개인자의 개수이고, argv[]는 그 매개인자에 대한 배열이다.

int형 변수 efd와 j를 선언

uint64_t형 변수 u 선언 (부호가 없는 64비트 정수형 변수)

ssize_t형 변수 s 선언 (signed int)

```c
if (argc < 2) {
       fprintf(stderr, "Usage: %s <num>...\\n", argv[0]);
       exit(EXIT_FAILURE);
   }
```

argc가 2보다 작을때 (매개인자가 없을 경우)

stderr라는 파일 포인터 변수에 " "의 내용을 적는다

exit(1) 함수로 프로그램 강제 종료

```c
efd = eventfd(0, 0);
   if (efd == -1)
       handle_error("eventfd");
```

eventfd()함수로 fd를 생성한 뒤 efd 변수에 값을 넣음

efd가 -1일 경우 handle_error()함수로 에러 메시지를 출력한 뒤 프로그램을 강제종료 한다

```c
switch (fork()) {
```

fork함수로 새로운 자식 프로세스를 생성하고 반환한다.

```c
case 0:
       for (j = 1; j < argc; j++) {
           printf("Child writing %s to efd\\n", argv[j]);
           u = strtoull(argv[j], NULL, 0);
                 write  /* strtoull() allows various bases */
           s = (efd, &u, sizeof(uint64_t));
           if (s != sizeof(uint64_t))
               handle_error("write");
       }
       printf("Child completed write loop\\n");

       exit(EXIT_SUCCESS);
```

자식 프로세스일 경우 fork함수가 0을 반환하기 때문에 이 코드는 자식 프로세스가 실행하는 코드이다.

매개인자의 개수만큼 for문을 돌린다.

자식 프로세스가 어떤 값을 받았는지 출력한다. (argv[j])

u에 argv[j]값을 가져와서 넣음

write()함수로 efd에 내용을 전송한다. (&u 버퍼의 내용을 uint64_t만큼 전송한다.)(성공했을 경우 s에 전송한 바이트 수가 들어옴, 실패했을 경우 -1)

s가 uint64_t 크기와 값지 않으면(전송이 바르게 되지 않았을 경우) "write" 에러 메시지를 출력하고 프로그램을 강제 종료한다.

write작업을 끝내면 "Child completed write loop"를 출력한다.

exit(1)로 프로그램을 강제 종료한다.

```c
default:
       sleep(2);

       printf("Parent about to read\\n");
       s = read(efd, &u, sizeof(uint64_t));
       if (s != sizeof(uint64_t))
           handle_error("read");
       printf("Parent read %llu (0x%llx) from efd\\n",
               (unsigned long long) u, (unsigned long long) u);
       exit(EXIT_SUCCESS);
```

부모 프로세스가 실행하는 코드이다.

sleep(2)함수로 2초 동안 기다린다.

read()함수로 efd값의 내용을 읽어온다. (efd의 내용을 uint64_t 크기만큼 읽어서 &u가 가리키도록 한다.) (성공했을 경우 s에 수신한 바이트 수가 들어옴, 실패했을 경우 -1)

s와 uint64_t의 크기와 같지 않으면(수신에 실패했을 경우) "read"로 에러 메시지를 출력하고 프로그램을 강제로 종료한다.

읽어온 efd 정보를 출력한다.

exit(1)로 프로그램을 강제 종료한다.

```c
case -1:
       handle_error("fork");
   }
```

실패했을 경우 fork함수는 -1을 반환한다. 이 코드는 fork함수가 실패했을 경우 실행되는 코드이다.

"fork" 에러 메시지를 출력하고 프로그램을 강제 종료한다.

