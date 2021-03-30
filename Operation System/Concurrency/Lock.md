# Lock


### Locks

critical section이 단일 원자(atomic) 명령처럼 실행되는지 확인한다.



Lock variable은 잠금 상태를 유지한다.

​	**available**(사용 가능)(**unlocked** or **free**)

​			lock을 사용하는 스레드가 없다.

​	**acquired**(획득한)(**locked** or **held**)

​		정확히 한 개의 스레드가 lock을 사용하고 있고 아마도 critial section에 있을 것이다.


<br>

### The semantics of the lock()

lock을 획득해라

lock을 획득한 다른 스레드가 없다면 스레드가 lock을 획득한다.

critical section을 입력한다.

​	이 스레드가 lock의 주인이라고

lock을 가지고 있는 첫 번째 스레드가 있는 동안에는 다른 스레드가 critical section에 들어가지 않는다.

<br>



### Pthread Locks - mutex

뮤텍스란 MUTual EXclustion으로 '상호 배제'라고 한다. Critical Section을 가진 스레드들의 running time이 서로 겹치지 않게, 각각 단독으로 실행되게 하는 기술이다.

POSIX 라이브러리가 lock에 사용하는 이름이다.

​	스레드 간에 상호 배제를 제공하는 데 사용된다.

​	서로 다른 변수를 보호하기 위해 다른 lock을 사용할 수 있다. → 동시성 향상(더 세분화된 접근방식)(???)

<br>


### Building a Lock

효율적인 lock은 낮은 비용으로 상호 배제를 제공한다.

lock을 구축하려면 **하드웨어**와 **OS**의 도움이 필요하다


<br>

### Evaluating locks - Basic criteria

**상호 배제(Mutual exclusion)**

lock을 획득하여 여러 개의 스레드가 critical section으로 들어오지 못합니까?

**공정성(Fairness)**

lock을 획득하려고 하는 각 스레드는 lock이 free가 되면 획득할 공정한 기회를 얻는가요?

**성능(Performance)**

lock을 획득하여 추가된 time overhead가 있나요? (추가적으로 발생한 시간이 있는지??)


<br>

### Controlling Interrupts

critical section에 대한 인터럽트를 사용하지 않음.

​	상호 배제를 제공하기 위해 사용된 가장 초기의 솔루션 중 하나

​	단일 프로세서(single-processor)시스템을 위해 개발됨

문제점

1. 응용프로그램을 지나치게 신뢰하게 된다.

   악의적인 프로그램이 프로세서를 독점할 수 있다.

2. 멀티 프로세서에서 동작하지 않음 (??) (→context switch??)

3. 인터럽트를 mask하거나 unmask하는 코드가 최신 CPU에서 느리게 실행된다. (??)


<br>

### Why hardware support needed?

First attempt : lock을 획득하였는지 아닌지 여부를 나타내는 flag를 사용

​	아래 코드에 문제가 있다.

문제 1 : 상호 배제가 없음 (시작하여면 flag=0이 있어야 함)

문제 2 : Spin-waiting은 다른 스레드를 기다리는 시간을 낭비한다



따라서 하드웨어에서 지원하는 원자 명령(atomic instruction)이 필요하다

​	원자 교환(atomic exchange)이라고도 하는 test-and-set 명령

------

<br>

### Test And Set (Atomic Exchange)

간단한 lock 생성을 지원하기 위한 명령이다.

​	ptr이 가리키는 old 값을 **리턴**한다.

​	해당 값을 새 값으로 동시에 **업데이트**(설정)한다.

​	이 일련의 작업은 원자적으로 수행된다. (performed atomically)


<br>

### A simple spin lock using test-and-set

참고 : 단일 프로세서에서 올바르게 작동하려면, 사전 예방적 스케줄러가(preemptive scheduler) 필요함


<br>

### Evaluating Spin Locks

정확성(Correctness) : yes

spin lock은 단일 스레드만 critical section으로 진입할 수 있도록 한다.

공정성(Pairness) : no

spin lock은 공정성을 보장하지 않는다. 스레드를 회전시키는 것은 영원히 회전할 수 있다.

성능(Performance) :

단일 CPU에서는 성는 오버헤드가 심각할 수 있다.

스레드 수가 CPU 수와 대략 같으면 spin lock은 상당히 잘 작동한다.

