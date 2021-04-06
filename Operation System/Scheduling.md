# Scheduling

#### Scheduling: Introduction

Workload 가정

1. 각 작업은 동일한 시간 동안 실행된다.
2. 모든 작업은 동시해 도착한다.
3. 모든 작업은 CPU만 사용한다.
4. 각 작업의 실행시간을 알 수 있다.

#### Scheduling Metrics (반환 시간)

- Performance metric: Turnaround time

  작업이 완료되는 시간에서 작업이 시스템에 도착한 시간을 뺀 시간입니다.

- 다른 metric은 공정성이다.

  스케쥴링에서 성능과 공정성이 상충(어긋난다)되는 경우가 많다.

------

비선점 : 자원을 가지고 있는 것이 선점을 하고 있으면 다른 것이 뺏을 수 없다.

선점 : 선점에 관계없이 우선순위 등의 관계로 선점을 뺏을 수 있다.

#### First In, First Out (FIFO)

- First come, First Served (FCFS)

  매우 간편하고 구현이 용이함

  

#### Why FIFO is not that great? - Convoy effect

- 가정 1 : 각 작업은 더 이상 동일한 시간 동안 실행되지 않는다.

  A를 먼저 실행하게 되면 B,C의 대기시간이 길어짐에 따라 평균적인 시간이 늘어나기 떄문에 FIFO는 좋은 방법이 아니다.

  ⇒ 짧은 일부터 먼저 하자



------

#### Shortest Job First (SJF)

- 가장 짧은 작업을 먼저 실행한 다음, 다음으로 짧은 작업을 실행함
- 비선점형 스케쥴러





#### SJF with Late Arrivals form B and C

- 가정 2 : 작업은 언제든지 도착할 수 있다.

  비선점의 경우 작업을 하고 있으면 다른 작업이 도착해서도 선점한 것을 뺏을 수 없다.

  ⇒ 반환시간이 길어질 수 있다.

------

#### Shortest Time-to-Completion First (STCF)

- SJF에 선점 추가

  PSJF (Perpective Shortest Job First)라고도 함

- 새 작업이 시스템에 들어간다 :

  나머지 작업 및 새 작업 결정

  남은 시간이 가장 짧은 작업 예약



------

#### New scheduling metric : Respones time (응답시간)

- 작업이 도착하는 시간부터 예약된 첫 번째 시간까지
  - STCF 및 관련 부문은 응답 시간에 특히 적합하지 않다.

------

#### Round Robin (RR) Scheduling

- 시간 슬라이싱 스케쥴링

  - time slice에 대한 작업을 실행한 다음 작업이 완료될때까지 run 큐에 있는 다음 작업으로 전환한다.

    주기적으로 인터럽트를 걸어주어서 프로그램들을 잘게 분해한다.

    - time slice를 스케쥴링 양자라고도 한다.

  - 작업이 완료될 때까지 반복적으로 수행한다.

  - RR은 공정하지만 반환시간과 같은 메트릭에서 성능이 떨어진다.

#### RR Scheduling Example

A, B, C 가 같은 시간에 도착하고 각 각 5초동안 실행된다.

- SJF (Bad for Response Time)

- RR with tile-slice of 1sec (Good for Response Time)

문맥교환이 이루어질 때, 시간이 걸린다. ( 캐시메모리가 삭제되고, 다시 복수하는 시간이 생각보다 오래 걸린다.)

따라서, 문맥교환의 횟수는 가능한 줄이는 것이 좋다.

그렇기 때문에 time slicing을 고려해야 한다. (overhead가 1%가 되게)

overhead : 어떤 처리를 하기 위해 들어가는 간접적인 처리 시간

------

#### The length of the time slice is critical

- 짧은 time slice
  - 응답 시간 향상
  - 컨텍스트 전환 비용이 전체 성능을 지배할 것이다.
- 긴 time slice
  - 전환 비용 상각
  - 더 나쁜 응답 시간

**시간 슬라이스의 길이를 결정하는 것은 시스템 설계자가 균형을 맞춘다.**

------

#### Incorporation I/O  (포함)

- 가정 3 : 모든 프로그램이 I/O를 수행한다.

- Example

  - A와 B는 각각 50ms의 CPU시간이 필요하다.

    - A가 10ms 동안 실행된 다음 I/O요청을 10ms 동안 실행한다.

  - B는 CPU를 50ms 동안만 사용한다.

  - 스케쥴러는 A를 먼저 실행한 다음 B를 실행한다.

    

IO는 자신이 직접 명령어를 가져오지 못하기 때문에 CPU에서 out 시리즈를 통해서 IO요청을 하게 된다. 이 부분이 A가 인터럽트를 거는 것,

IO가 작업이 끝나면 IO에 있는 버퍼가 메인 메모리에 있는 버퍼에 값을 주고 그것을 CPU가 읽음으로써 작업이 끝난다.

DMA polling : CPU가 IO 작업이 끝났는지 물어보는 것

interrupt : IO가 끝났다는 것을 알려주는 것



**CPU 사용률 극대화**

A를 실행하다가 IO를 요청하면, B와 분배교환이 되면서 B가 실행되고, IO는 따로 실행이 된다.

→ IO가 작업이 끝나면 인터럽트를 발생시켜 B의 작업을 멈추고 A가 일을 진행하게 만든다.

- 작업이 I/O요청을 시작할 때
  - 작업이 I/O 완료 대기 중 차단됨
  - 스케쥴러는 CPU에서 다른 작업을 예약해야함
- I/O가 완료되면
  - 인터럽트가 발생함
  - OS는 프로세스를 자단된 상태에서 다시 준비 상태로 이동함
