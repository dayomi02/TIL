## 특징

- 리눅스 커널의 Interrupt Bottom-Half 처리기 중 가장 큰 부분으로 동작한다.
- softirq는 최고 우선 순위의 ksoftirqd 스레드가 각각의 CPU에서 동작된다.
- 기존의 많은 드라이버들이 interrupt bottom-half 처리기로 tasklet을 많이 사용해었는데 tasklet 인터페이스가 그대로 softirq의 한 부분으로 동작하면서 기존 tasklet을 사용하던 드라이버들을 흡수하였다.

### ksoftirqd thread

- Soft IRQ 처리용으로 생성된 스레드
- ksoftirqd이란 per-cpu 타입 프로세스이다.
- 즉 CPU 개수만큼 생성해서 정해진 CPU 내에서만 실행한다.


[[리눅스커널] SoftIRQ: ksoftirqd 스레드란](http://egloos.zum.com/rousalome/v/9978671)

<br>

## Context

### irq context

- hardirq라고도 불린다.
- 처음 호출 시 irq context 상태에서 직접 핸들러 함수를 호출하여 처리한다.

### process context

- task context 또는 thread context 라고도 불린다.
- irq context에서 처리하다가 2ms 이상 처리가 길어지면 process context에서 동작하는 ksoftirqd 스레드를 깨워서 softirq 처리를 의뢰한다.
- irq context에서 계속 처리하지 않고 ksoftirqd 같은 태스크에 처리를 의뢰하는 것은 대량의 인터럽트 처리 를 irq context에서 수행하느라 cpu를 독식하여 일반 태스크들이 동작하지 못하는 기아(starvation) 현상을 없애기 위함이다.
