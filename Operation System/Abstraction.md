# Abstraction

## CPU virtualizing

- OS는 많은 가상 CPU가 존재한다는 착각을 촉진할 수 있다.
- Time sharing : 한 프로세스 실행 후 중지 및 다른 프로세스 실행
    - 프로그램 하나가 CPU를 독점해서 사용하는 것이 아니라, 시간을 분할해서 사용하게 만듦.
    - 잠재적인 비용은 성능이다. (성능의 손실 없이 가상화를 해냄)
<br>

## A Process

A process is a running program.

process : 프로그램이 실행되기 위해 추상화된 상태

program : code, data가 들어있는 실행파일

- 프로세스 구성
    - Memory (address space)
        - Instructions (명령)
        - Data section
    - Registers
        - Program counter (PC)
        - Stack pointer (SP)
<br>

## Process API

- Create

    프로그램을 실행할 새로운 프로세스 생성

- Destroy

    제어가 안 되는 프로세스 정지

- Wait

    프로세스가 중지될 때까지 기다림
<br>

## Process Creation

1. 프로그램 코드를 메모리에 **로드**한다, 프로세스의 주소 공간 안에 
    - 프로그램은 실행 파일 형식으로 디스크에 처음 상주한다.
    - OS는 로딩 프로세스를 느리게 수행한다.
        - 프로그램 실행 시 필요한 코드 또는 데이터만 로드한다
2. 프로그램의 run-time **스택**이 할당된다.
    - 지역변수, 함수 매개 변수 및 반환 주소에 스택을 사용한다.
    - 객체로 스택 초기화 ⇒ argc ,  main()의 argv 배열 함수
3. 프로그램의 **힙**이 생성된다.
    - 명시적으로 요청된 동적 할당 데이터에 사용된다.
    - 프로그램은 malloc()을 호출하여 이러한 공간을 요청하고 free()를 호출하려 여유 공간을 확보한다.
4. OS가 몇 가지 다른 초기화 작업을 수행한다.
    - input/output (I/O) 설정

        각 프로세스에는 기본적으로 3개의 open file descriptor가 있다.

        표준입력, 출력, 오류

5. 진입점, 즉  main()에서 running **프로그램을 시작**한다.
    - OS가 CPU의 제어를 새로 생성된 프로세스로 전송한다.
<br>

## Loading: From Program To Process

Loading : no-disk 프로그램을 가져와서 프로세스의 주소 공간으로 읽는다.

protection (보호의) : 어떤 프로그램의 에러생태에 대해서 다른 프로그램들고 영향을 받지 않도록 하는 것. 따라서 각각의 프로그램의 가상 메모리 밖에서의 일들은 관여하지 않도록 만든다.

키보드나 모니터, IO 같은 경우 그것을 추상화 시켜서 파일형태로 만들어서 읽거나, 쓸 수 있게 만든다.

두 개의 프로그램이 번갈아 가변서 실행이 될 때, 중간값을 어떻게 저장할 것인가? ⇒ 실행되었던 흐름른 저장하지 않고 중간값을 정확히 저장한다. 중간의 단면을 정확히 캐치하고 이 후 다시 불러올 때 중간값을 집어넣어 주게 된다.
<br>

## Process States

- Running
    - 프로세서에서 프로세스가 실행 중이다.
- Ready
    - 프로세스가 실행 준비가 되었지만 몇 이유로 OS가 현재 시점에서 ㅅㄹ행하지 않기로 선택함.
- Blocked
    - 공정에서 어떤 작업이 수행됨.
    - 디스트에 대한 I/O 요청을 시작하면 차단되어 다른 프로세스가 프로세서를 사용할 수 있다.
<br>

## Rrocess State Transition

프로세스가 진행중이다.

I/O를 초기화하게 되면 System call로 write()를 부르게 된다.

이렇게 되면 Blocked 상태가 된다.

I/O의 요청이 다 끝나게 되면 Ready 상태로 변한다.

보기에는 write에서 리턴한 것처럼 보인다.

다시 CPU가 주어지게 되면, 화면에 띄워주거나, 입력받게 된다.
<br>

## Data structures

- OS 에는 다양한 관련 정보를 추적하는 몇 가지 주요 데이터 구조가 있다.
    - Process list
        - Ready processes
        - Blocked processes
        - Current running process
    - Register context
- PCB (Process Control Block)

    C-structure는 각 프로세스에 대한 정보를 포함한다.

    C-structure (Control-structure) : 프로그램에서 실행 흐름을 제어하는 데 사용되는 제어 구조.

    프로세스에 대한 중요한 정보를 가지고 있는 자료.

    CPU가 처리하던 작업의 내뇽들을 자신의 PCB에 저장하고, 다음에 다시 CPU를 점유하여 작업을 수행해야 할 째 PCB로부터 정보를 넘겨와서 작업을 진행한다.
