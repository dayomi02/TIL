## System Software overviwe


H/W 위에서 S/W 가 동작하는 방식으로 이루어져있다.

---


- CPU
    - Registers : 연산장치에 저장하기 전에 잠깐 저장하기 위한 공간, 작은 용량의 값들을 주로 처리, 여러 종류의 레지스터가 존재함
    - ALU(Arithmetic & Logic Unit) : 계산을 하는 장치, 연산을 하는 장치
- Memory
    - RAM : 저장장치, 레지스터보다는 빠르지만 롬보다는 느림, 레지스터에서 처리하기 힘든 용량이 큰 값을 처리
    ⇒ RAM이 크면 컴퓨터가 빠르다라고 말함
- I/O Controllers : 버스로 연결해서 사용함
- I/O Devices : 주변 장치들

---


과정 

> c → compiler → .exe

- 위 사진에서 .o는 object 파일을 말한다.
- Linker 작업에서 makefile을 보고 link작업을 진행한다.
- Compiler(cc1), Assembler(as)는 컴파일러에서 진행되는 단계이다.
- 최종 정리
    - 컴파일러에서 오브젝트 파일(.o)을 만든다.
    - Link 작업을 진행하는 Linker 단계가 존재한다.

---

- 시스템 소프트웨어가 어떤 관계로 동작하는지 나타낸 그림이다.
- 각각 버스로 연결되어있는데 버스 이름은 각각 다르다.
<br>

## Kinds of System Software

OS

Divice Driver

Shell

Hypervisor

펌웨어

등등
<br>

## System Software의 사용

그래픽 카드

휴대폰 (카메라, 센서 등을 제어)

자동차

국방

⇒ 칩이 들어가는 순간 system  software가 필요하다고 말할 수 있다.
<br>

## System software 기업들

Intel ⇒ 개발과 생산을 모두 함, CISC

AMD ⇒ 생산만 함, CISC

ARM ⇒ 개발된 개발도. 개발도를 보고 다른 회사에서 변형해서 사용함, 

RISC, Soc(System on Chip)

        Ex) Apple의 M1칩
<br>

## Historu of Kernel

- GNU (GNU is not Unix)
    - Linux OS는 GUN의 한 종류이다.
- 데니스리치
    - GUN와 오픈소스의 베이스를 만든 사람이다.
    - 교육용 B언어를 만듬.
    - Kernel을 만들기 위해 C언어를 만듬.
- 어셈블리어
<br>

## OS & Kernel

Kernel은 정확하게 무엇인지 명시되어 있는 것이 아님. 개념적으로 존재함.

OS를 Kernel이라고 부르기도 함.

OS의 역할이 Kernel의 역할이었는데 시간이 지나면서 OS의 역할이 많아지면서 OS와 Kernel을 분리하게 되었다.

Kernel을 제외한 OS의 역할은 User를 위한 것들이다.

- Shell
    - User와 Kernel을 연결해주는 역할을 한다.
    - User가 Shell을 통해서 Kernel을 사용한다.
- System에서 보았을 때, User와 Application은 비슷하다. 같은 레벨이다.
<br>

## Virtualization Overview

- 가상화는 가상 시스팀과 실제 시스템 사이의 동형의 구성을 말한다.
- H/W와 S/W를 속이는 것이다.
- IBM에서 OS가상화를 먼저 사용함 (은행, 업데이트)
<br>

## Memory Virtualization

- 프로세스를 메모리에 페이징해서 넣는다.
- 페이징 한 메모리를 가상화 메모리에 넣는다.

    ---

실제 컴퓨터에서 사용중인 기술이다.

OS 가상화 = OS를 속인다.

OS 가상화를 사용하면 속도가 느려질 뿐 작동이 멈추거나 병목현상이 발생하지는 않는다.
