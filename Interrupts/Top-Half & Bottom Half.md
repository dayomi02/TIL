## Top-Half & Bottom Half

"인터럽트 처리를 하는 시간이 길면 길수록 시스템이 멈춘 것 같이 보일 수 있다"

"인터럽트가 발생했을때 데이터를 가져오는 등의 기능은 반드시 바로 처리해야 하고 속도도 빠르니까 데이터 가져오는 것까지만 잽싸게 처리하고, 그 데이터를 가져온 이후 동작은 꼭 지금 해야 하는 것은 아니니 나중에 처리하자"

### Two part interrupt handler

- top-half 부분의 인터럽트 핸들러는 최소한의 일을 수행하고 약간 지연되어 처리되어도 상관 없는 부분은 bottom-half 부분에서 처리되게 하는 기술
- 데이터를 가져오는 동작 : Top
가져온 데이터를 처리하는 동작 : Bottom

<br>

## Component

### Interrupt context (top-half interface)

- 처음 진입 되면 새로운 인터럽트를 받아들일 준비를 하는 부분과 bottom half context로 데이터를 전달하는 부분으로 나뉜다.
- sleep API의 사용이 불가능하며 최대한 빠르게 처리를 완료하고 복귀하도록 되어 있다.

### Bottom halves

- bottom half 구조의 첫 구현이다.
- 한 번에 하나의 인터럽트 처리만 가능하다.
- core가 여러 개 있을 때에도 한번에 하나 씩 만 처리하는 단점이 있다.
- sleep API의 사용이 불가능하다.

### Task queues

- bottom halves에 등록된 인터럽트 핸들러 중 특별히 느리게 처리되는 것들을 별도의 스레드에서 처리하도록 구현한다.
- process context에서 처리된다.
- sleep API가 사용 가능하다.

### Softirqs

- 빠른 처리를 위해 구현된 인터럽트 핸들러가 각각의 코어에 동작 가능하게 설계되었다.
- 디바이스 드라이버 등에서 동적으로 추가할 수 없다.
- 빠르게 처리할 주요 인터럽트 핸들러들만 포함되었다.
- bottom-half로 구분되어 있지만 interrupt context 및 process context 모두에서 호출될 수 있는 특성을 가지고 있다.
- sleep API의 사용이 불가능하다.

### Tasklet

- 같은 타입을 사용하는 tasklet은 멀티 코어일지라도 한 번에 하나만 동작한다.
- 사용자가 인터럽트 핸들러를 동적으로 추가할 수 있다.
- bottom-half로 구분되어 있지만 interrupt context 및 process context 모두에서 호출될 수 있는 특성을 가지고 있다.
- 현재는 없어지고 Softirq에 포함되어 있다. (API 레퍼되어 그대로 사용 가능)
- sleep API의 사용이 불가능하다.

### Work queues

- Task queues를 대체하여 개발되었다.
- process context에서 처리된다.
- 각각의 코어에서 처리하다 최근에는 poll개념으로 동시 수행 개념이 도입되었다.(Concurrency Managed Work Queues)

---


최근 커널은 가장 빠르게 처리할 hrtimer(High Resolution kernel Timer)인터럽트는 다시 interrupt context로 되돌아와서 처리하고

그 외에 가장 빠르게 처리해야 할 인터럽트 핸들러들이 softirq에 동작한다.

그 외의 인터럽트 핸들러 들은 별도의 스레드에서 work queues를 통해 동작한다.
