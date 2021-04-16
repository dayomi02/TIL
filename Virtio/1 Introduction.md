이러한 디바이스는 가상 환경에서 발견되지만 설계상 가상 시스템 내에서 게스트에게 물리적 디바이스처럼 보입니다. 이 문서에서는 이러한 디바이스를 물리적 디바이스로 취급합니다. 이러한 유사성을 통해 게스트는 표준 드라이버와 검색 메커니즘을 사용할 수 있습니다.

가상 디바이스를 위한 직선적이고 효율적이며 표준적이며 확장 가능한 메커니즘을 보유해야 한다

Straightforward (간단한 방법) : 
Virtio 디바이스는 모든 디바이스 드라이버 작성자에게 익숙한 인터럽트와 DMA의 일반적인 버스 메커니즘을 사용합니다. : 그냥 평범한 장치일 뿐.

Efficient (효율성) :
Virtio 디바이스는 입력 및 출력 모두를 위한 설명자 링으로 구성되며, 드라이버와 디바이스 쓰기 모두에서 동일한 캐시 라인에 캐쉬 효과를 방지하기 위해 깔끔하게 배치됩니다.

Standard (표준) :
Virtio는 장치가 연결된 버스를 지원하는 것 외에 작동하는 환경에 대해 어떠한 가정도 하지 않습니다.

Extensible (확장 가능) :
Virtio 디바이스에는 디바이스 설정 중에 게스트 운영 체제에서 승인하는 기능 비트가 포함되어 있습니다.
이렇게 하면 앞뒤 호환이 가능합니다.