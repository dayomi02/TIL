### Thread

실행중인 프로세스를 위한 새로운 추상화.

실행중인 프로세스의 흐름

**Multi-threaded program**

- 다중 스레드 프로그램에 둘 이상의 실행 지점이 있다.

- 여러 대의 PC(Program Counter)

- 같은 주소 공간을 공유한다. (같은 힙 영역을 공유해서 사용한다.)

  

### Context switch between threads

각 스레드는 자체 프로그램 카운터 및 레지스터 집합을 가지고 있다

​	각 스레드 상태를 저장하려면 하나 이상의 thread control blocks(TCB)이 필요하다.

실행중인 하나(T1)에서 실행 중인 하나(T2)로 전환할 때

​	T1의 레지스터 상태가 저장된다.

​	T2의 레지스터 상태가 복원된다.

​	주소 공간은 그대로 유지한다.



### The stack of the relevant thread

스레드당 하나의 스택이 있다.

code segment : 명령이 있는 곳

heap segment : malloc'data를 포함, 동적 데이터 구조 (아래로 증가) (+)

stack segment : 지역 변수를 포함, 루틴에 대한 인수, 값 등을 반환 (위로 증가) (-)



### Race condition

두 개의 스레드가 있는 예제

- counter = counter + 1 (50)

- 52가 될 것으로 예상한다. 하지만 51이다.

  

### Critical section

Critical Section : 프로그램 상에서 동시에 실행될 경우 문제을 일으킬 수 있는 부분.

공유 변수에 액세스하는 코드 조각이며 둘 이상의 스레드에서 동시에 실행할 수 없다.

​	critical section을 실행하는 여러 스레드는 Race condition(레이스 상태)를 발생시킬 수 있다.

​	critical section에 대한 **원자성(atomicity**) 지원 필요 **(상호 배제)(mutual exclusion)**



### lock

critical section이 단일 원자 명령처럼 실행되는지 확인한다. (**원자적으로 일련의 명령을 실행한다.**)
