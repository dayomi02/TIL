## irqchip

irqchip은 일반적으로 "interrupt controller"라고 하는 KVM의 이름이다.

이것은 많은 인터럽트 신호(USB controller, disk controller, PCI card, serial port 등)를 가져와 CPU에 제공하는 하드웨어이다. 인터럽트를 사용하도록 설정된 CPU 제어, 새 인터럽트가 도착하면 알림, 처리한 인터럽트를 해제하는 등의 방식으로 한다.
