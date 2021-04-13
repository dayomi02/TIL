## Per cpu

per-cpu 영역은 커널의 메모리 관리 기법 중의 하나로 각 cpu 별로 사용하는 데이터들을 완전히 분리하여 동기화를 사용하지 않고도 안전하고 빠르게 데이터에 접근하기 위한 기법이다. 

어떤 자료 구조를 per-cpu를 통해 관리하고 싶다면 해당 객체를 시스템 내의 cpu 수 만큼의 배열로 생성하고 자기 cpu 번호에 맞는 원소만 참조하면 된다.

<br>

동일한 변수에 대해 각 cpu별 독립적인 메모리 공간을 제공하는 것을 per-cpu변수라 한다. SMP(Symmetry Multi Processing)에서 cpu가 동시에 접근하는 자원에 대해서 캐시에 대한 메커니즘이 필요함. per-cpu변수를 이용하면 개별 공간에 접근하므로 동기화 메커니즘이 필요 없어 속도가 빠르다.

per-cpu는 변수를 cpu 수 만큼 별도로 할당하는 메모리 관리 기법이다. 이렇게 cpu별로 분리된 공간을 사용하면 cpu들 사이에 동기화 메커니즘이 필요 없어 빠른 성능을 얻을 수 있어, 프로세서의 캐시 히트율을 높일 수 있다는 장점도 있다.