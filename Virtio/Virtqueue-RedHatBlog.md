# Virtqueues and virtio ring: How the data travels

[Virtqueues and virtio ring: How the data travels](https://www.redhat.com/en/blog/virtqueues-and-virtio-ring-how-data-travels)

### Buffers and notification : The work routine

virtqueue는 호스트가 읽거나 쓰는 중 사용하는 게스트 버퍼의 queue이다. 버퍼는 장치 관점에서 읽기 전용이거나 쓰기 전용 일 수 있지만 둘 다는 아니다.

드라이버에서 장치로의 알림(초인종) 방법을 제공하여 하나 이상의 버퍼가 queue에 추가되었음을 알리고, 그 반대의 경우 장치가 드라이버를 중단하여 사용 된 버퍼에 신호를 보낼 수 있다. 

드라이버와 장치는 dispatching overhead 를 줄이기 위해 알림을 내보내지 않도록 상대방에게 조언할 수 있다. 이 작업은 비동기식이다.

---

### Split virtqueue : The beauty of simplicity

분할 된 virtqueue 형식은 virtqueue를 세 영역으로 분리한다. 여기서 각 영역은 드라이버 또는 장치에서 쓸 수 있지만 둘 다는 쓸 수 없다.

- Descriptor Area (설명자 영역) : 버퍼를 설명하는 데 사용됨
- Driver Area (드라이버 영역) : 드라이버가 장치에 제공하는 데이터. avail virtqueue
- Device Area (장치 영역) : 장치에서 드라이버에 제공하는 데이터. used virtqueue

드라이버가 직접 액세스 할 수 있으려면 드라이버의 메모리에 할당되어야 한다. 버퍼 주소는 드라이버의 관점에서 저장되며 장치는 주소 변환을 수행해야 한다. 

후자의 특성에 따라 장치가 액세스하는 방법은 여러 가지가 있다.

- Hypervisor의 에뮬레이트 된 장치 (qemu)의 경우 게스트 주소는 자체 프로세스 메모리에 있다.
- vhost-net 또는 vhost-user와 같은 다른 에뮬레이션 된 장치의 경우 POSIX 공유 메모리와 같은 메모리 매핑을 수행해야한다. 해당 메모리에 대한 파일 설명자는 가상 호스트 프로토콜을 통해 공유됩니다
- 실제 장치의 경우 일반적으로 IOMMU를 통해 하드웨어 수준의 변환을 수행해야한다.

---

### Descriptor ring : Where is my data?

설명자 영역(설명자 링)은 이해해야 하는 첫 번째 영역이다. 여기에는 게스트 주소 지정 버퍼의 배열과 길이가 포함된다. 각 디스트립터에는 더 많은 정보를 나타내는 플래그 세트도 포함되어 있다. 

예를 들어 0x1 비트가 설정된 경우 버퍼는 다른 설명자 버퍼에서 계속되고, 0x2가 설정된 경우 버퍼는 장치에 대해 쓰기 전용이다, 삭제된 경우 읽기 전용이다.

이것은 단일 디스크립터의 레이아웃이다. 리틀 엔디안 형식의 N 비트에 대해 leN 을 호출한다.

```c
struct virtq_desc { 
        le64 addr;
        le32 len;
        le16 flags;
        le16 next; // Will explain this one later in the section "Chained descriptors"
};
```

---

### Avail ring : Supplying data to the device

Driver Area (드라이버 영역) 

다음으로 흥미로운 구조는 드라이버 영역 또는 Avail ring이다. 드라이버 장치가 사용할 설명자를 배치하는 공간이다. 여기에 버퍼를 배치한다고 해서 장치가 즉시 소비해야 한다는 의미는 아니다. 

제공 목록에는 드라이버만 쓸 수 있고 장치는 읽을 수만 있는 두 가지 중요한 필드가 있다. (idx and flags)

idx 필드는 드라이버가 제공 목록에 다음 설명자 항목을 넣을 위치를 나타낸다.(queue의 크기 모듈로) 반면에 flags의 최하위 비트는 드라이버가 알림을 받을 것이지 여부를 나타낸다. (called `VIRTQ_AVAIL_F_NO_INTERRUPT`)

이 두 필드 뒤에는 디스크립터 링과 길이가 같은 정수 배열이 있다. 따라서 avail virtqueue  레이아웃은 다음과 같다.

```c
struct virtq_avail {
        le16 flags;
        le16 idx;
        le16 ring[ /* Queue Size */ ];
};
```

**Figure 1 : Driver writes a buffer in descriptor ring** 

(드라이버가 설명자 링에 버퍼를 쓴다.)

![https://s3-us-west-2.amazonaws.com/secure.notion-static.com/a6b96b4f-4404-48db-9dad-c42ab22df483/Untitled.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/a6b96b4f-4404-48db-9dad-c42ab22df483/Untitled.png)

0x8000 위치에서 시작하는 2000byte 길이의 버퍼와 아직 항목이 없는 avail ring이 있는 descriptor table을 보여준다. 모든 단계가 끝나면 descriptor 영역을 강조하는 구성 요소 다이어그램이 업데이트된다.

드라이버의 첫 번째 단계는 메모리에 버퍼를 할당하고 채우는 것이다. ("버퍼를 사용 가능하게 만드는 프로세스") (1단계)

그 후 descriptor의 영역에서 사용 가능하게 만드는 것 (2단계)

**Figure 2 : Driver offers the buffer with avail ring**

(드라이버에서 avail ring을 사용해서 버퍼를 제공한다.)

![https://s3-us-west-2.amazonaws.com/secure.notion-static.com/ac0f7139-88ca-4aca-8a1e-11049a168d0d/Untitled.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/ac0f7139-88ca-4aca-8a1e-11049a168d0d/Untitled.png)

descriptor 항목을 채운 후 드라이버는 avail ring을 사용하여 이를 알린다. avail ring의 첫 번째 항목에 descriptor의 인덱스 #0을 쓰고 이에 따라 idx 항목을 업데이트 한다. 

chained 버퍼(next)를 제공하는 경우 descriptor head index만 이런 방식으로 추가해야 하며, avail idx는 1만 증가한다.

(3단계)

**Diagram : Process to make a buffer available**

(버퍼 사용 가능 프로세스)

![https://s3-us-west-2.amazonaws.com/secure.notion-static.com/9b322034-60d2-41b7-8dfc-0ff3fbf7c90b/Untitled.png](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/9b322034-60d2-41b7-8dfc-0ff3fbf7c90b/Untitled.png)

지금부터, 드라이버는 사용 가능한 descriptor 또는 노출된 버퍼를 수정해서는 안된다. 
: 장치의 제어 하에 있다.

이제 드라이버는 해당 순간에 알림을 사용하도록 설정한 경우 장치에 알려야 한다.(more on how the device manages this later) (4단계)

avail ring은 descriptor 영역과 동일한 수의 descriptor를 보유 할 수 있어야 하며 descriptor 영역은 2의 거듭 제곱을 가져야 하므로 idx는 어느 시점에서 자연스럽게 래핑된다. 

descriptor는 avail ring에 임의의 순서로 추가 할 수 있다. descriptor는 descriptor table entry 0에서 시작하거나 다음 descriptor에서 계속할 필요가 없다.

---

### Chained descriptor : Supplying large data to the device

(장치에 대용량 데이터 제공)

드라이버는 다음 멤버를 사용하여 둘 이상의 descriptor를 연결할 수도 있다. descriptor의 NEXT(0x1)플래그가 설정되면 데이터는 다른 버퍼에서 계속되어 descriptor chain을 만든다. chain의 descriptor는 플래그를 공유하지 않는다. 일부 descriptor는 읽기 전용 일 수 있고 다른 descriptor는 쓰기 전용 일 수 있다. 이 경우 쓰기 전용 descriptor는 모든 쓰기 전용 descriptor뒤에 와야 한다.

장치에 chain 버퍼가 표시됨

---

### Used ring: When the device is done with the data

(장치에서 데이터 작업이 완료된 경우)

장치는 사용 된(읽기 또는 쓰기) 버퍼를 드라이버에 반환하기 위해 used ring을 사용한다. avail ring 처럼 flags와 idx 멤버가 있다. 이제 알림 플래그가 VIRTQ_USED_F_NO_NOTIFY라고 불리지만 레이아웃과 용도는 동일하다.

그 다음에는 used descriptor의 배열을 유지한다. 이 배열에서 디바이스는 descriptor 인덱스 뿐만 아니라 쓰기 시 사용된 길이도 반환한다.

```c
struct virtq_used {
        le16 flags;
        le16 idx;
        struct virtq_used_elem ring[ /* Queue Size */];
};

struct virtq_used_elem {
        /* Index of start of used descriptor chain. */
        le32 id;
        /* Total length of the descriptor chain which was used (written to) */
        le32 len;
};
```

chain의 descriptor를 반환하는 경우, chain head의 ID만 반환 되고, 모든 descriptor를 통한 전체 길기만 반환 되며, 데이터를 읽을 때는 증가 시키지 않는다. (?)

descriptor table은 전혀 터치 되지 않으며 읽기 전용이다.

used buffer를 만드는 프로세스 다이어그램 5단계이다. (5단계)

예를 들어 장치가 chain된 descriptor 버전에 노출된 chain의 descriptor를 사용하는 경우 : 

**Figure 4 : Device returns buffer chain**

(장치가 buffer chain 반환)

마지막으로, 장치는 드라이버가 알림을 받기를 원한다고 판단되면 사용 된 큐 플래그를 사용하여 드라이버에게 알린다. (6단계)

