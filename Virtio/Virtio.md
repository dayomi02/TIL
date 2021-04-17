# Virtio

Virtual I/O의 약자로써, Guest OS와 Host간 para virtualized I/O를 지원하기 위한 표준화1된 인터페이스이다.

QEMU를 이용해서 전 가상화로 VM을 돌릴 경우 Guest OS에 별다른 수정 사용 할 수 있다는 장점이 있으나 매번 Guest의 명령어를 트램해서 장치를 에뮬레이션 해줘야 하므로 느리다는 단점이 있다. 

이런 문제를 해결하고자 가상화 개발자는 virtio라는 구조를 창안해냈다. 이 구조의 개념은 일부 장치에 대해서는 매번 트랩해서 에뮬레이션 하지 말고 Hypervisor와 Guest가 바로 통신 할 수 있는 채널을 만들어 불필요한 오버헤드를 줄이자는 것이다. 이를 위해 Guest에는 특정 장치가 Host와 통신하시 위한 Frontend 드라이버가 있어야하고 마찬가지로 Hypervisor에도 Guest와 특정 장치가 통신 할 수 있는 backend 드라이버가 필요하다.


virtio는 Guest의 일부 수정이 필요하다는 단점이 있지만 얻게될 성능상 이득을 고려하면 이정도 불편함은 감수해야 할 것 같다. Linux인 경우에는 몇몇 장치들에 대해선 virtio frontend 드라이버 코드가 이미 커밋돼있어 찾아서 사용하면 된다.
