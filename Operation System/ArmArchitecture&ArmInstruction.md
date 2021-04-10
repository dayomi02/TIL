## Program Status Register

- ARM의 PSR 레지스터
    - 1 CPSR
    - 5 SPSR (각 작동 모드를 위한)

- PSR 레지스터 필드
    - Condition(조건) flag
    ALU(산술 논리 장치) 처리 결과 반영
    오버헤드가 자주 일어나기 때문에 1비트로 하나의 구조체를 표현
    - Control(제어) bits
    CPU 상태를 제어하기 위해


## PSR Register - flag bits

- Flag 비트는 바로 앞의 ALU 계산 결과를 나타낸다.
    - 'N' bit : Negative flag

        ALU 계산 시 음수 값이 생성됨

    - 'Z' bit : Zero flag

        ALU 계산으로 0이 생성됨

    - 'C' bit : Carry flag

        ALU 계산 또는 shift 작동으로 Carry 발생

    - 'V' bit : Overflow bit
- 추가 비트
    - 'Q' bit : saturation bit
    - 'J' bit : jazelle state bit

## PSR Register - control bits

- PSR control bit가 프로세서 작동 모드, 인터럽트 및 기타 프로세서 상태를 변경한다.
    - I/F bit

        IRQ 또는 FIQ 사용/사용 안 함
        인터럽트를 무시할 것인가, 아닌가

    - T bit

        Thumb mode 켜기/끄기

        'BX' 명령어를 통해서만 제어 가능

    - Mode bit


---

## Memory Architecture

- Endian
    - Big/Little endian (ARM은 두 가지 모두를 지원함)
    - 하드웨어 설정을 통해 구성
- Data access types
    - Byte : 8bit
    - Halfword : 16bit
    - Word : 32bit (32 bits 프로세서)
    64 bits 프로세서에서는 8byte
- Aligned / Un-aligned access (정렬 / 비정렬)
    - 모든 메모리 엑세스는 단어별로 정렬되어야 함 (half-word)
    - 최신 아키텍쳐로 비정렬 엑세스 기능
        - 기존에는 항상 데이터 중단이 발생함

CPU는 32 bit씩 읽어오게 됨 (32개의 핀이 존재) 

⇒ 명령어를 읽을 때 기본적으로 모든 명령어는 정렬되어 있다고 가정함

## Little-Endian vs Big-Endian

- Big-Endian

    MSB (Most Significant Byte)(가장 중요한 바이트) 는 메모리 내 낮은 주소에 위치함. (Bit 24 ~ 31)

- Little-Endian

    LSB (Least significant Byte)(덜 중요한 바이트)는 메모리 내 낮은 주소에 위치함. (Bit 0 ~ 7)

## Aligned and Un-aligned Accesses

정렬되어 있지 않은 접근을 하기 위해서 조합을 하게 되면 속도가 즈려진다.

따라서 abort exception이 발생한다.

