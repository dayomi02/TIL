## 익셉션 백터 테이블
전원이 켜지면 ARM은 익셉션 벡터 테이블의 리셋 벡터를 읽는다. 0x00000000 메모리 주소에 익셉션 벡터 테이블을 배치한다. 이 테이블의 위치는 조정 가능하지만, 대부분 바꾸지 않고 기본 위치를 사용한다. 

익셉션이 총 7개 있으며 중간은 0x14 오프셋은 사용하지 않는다. ARM은 익셉션 벡터 테이블에 정의된 상황이 발생하면 프로그램 카운터(PC)를 익셉션 백터 테이블에 정의된 오프셋 주소로 강제 변환된다. 그리고 테이블에 있는 명령을 바로 실행한다.

<br>

익셉션 벡터 테이블의 구성
| Offset | Name                  | Ex                                            |
| ------ | --------------------- | --------------------------------------------- |
| 0x00   | Reset                 | 전원이 켜지면 실행됨                          |
| 0x04   | Undifined Instruction | 잘못된 명령어를 실행시켰을 때                 |
| 0x08   | SVC(Supervisor Call)  | SVC 명령으로 발생시키는 익셉션                |
| 0x0C   | PrefetchAbort         | 명령어 메모리에서 명령어를 읽다가 문제가 생김 |
| 0x10   | DataAbort             | 데이터 메모리에서 데이터를 읽다가 문제가 생김 |
| 0x14   | Not used              | 사용하지 않음                                 |
| 0x18   | IRQ interrupt         | IRQ 인터럽트가 발생했을 때                    |
| 0x1C   | FIQ interrupt         | FIQ 인터럽트가 발생했을 때                    |


<br>

익셉션 벡터 테이블의 익셉션은 각각 4바이트씩 할당되어있다. 32비트 머신이기 때문에 한 익셉션에 명령어 한 개만 실행할 수 있다. 익셉션 처리에 필요한 코드가 개발자마다, 시스템마다, 펌웨어마다 다 다르기 때문에 명령어를 한 개만 실행할 수 있도록 공간을 배정한 것이다. 특정한 크기를 예약해 놓을 경우 어떤 사람은 크기가 부족하고 어떤 사람은 크기가 남아서 메모리가 낭비되는 상황이 발생할 수 있다. 그렇게 떄문에 명령어를 쓸 수 있는 최소 크기(4바이트)를 배정하고 거기에 브랜치 명령어를 써 놔서 익셉션을 처리하는 코드로 점프하게 만드는 것이다. 여기서 익셉션을 처리하는 코드를 익셉션 핸들러(exception handler)라고 부른다.

<br>

- 익셉션이 발생하면 ARM 코어는 PC를 익셉션 벡터 테이블의 익셉션 벡터 오프셋으로 변경한다. 
- 익셉션 벡터 오프셋은 명령어 한 개만 쓸 수 있는 크기이며, 그곳에 브랜치 명령을 작성한다.
- 브랜치 명령에 따라 점프하면 익셉션 핸들러로 진입하게된다.
- 익셉션 핸들러에서 익셉션을 처리한다.

<br>

익셉션 벡터 테이블 코드 (/boot/Entry.S)

```c
...
vector_start:
		LDR PC, reset_handler_addr
		LDR PC, undef_handler_addr
		LDR PC, svc_handler_addr
		LDR PC, pftch_abt_handler_addr
		LDR PC, data_abt_handler_addr
		B .
		LDR PC, irq_handler_addr
		LDR PC, fiq_handler_addr

		reset_handler_addr:     .word reset_handler
        undef_handler_addr:     .word dummy_handler
        svc_handler_addr:       .word dummy_handler
        pftch_abt_handler_addr: .word dummy_handler
        data_abt_handler_addr:  .word dummy_handler
        irq_handler_addr:       .word dummy_handler
        fiq_handler_addr:       .word dummy_handler
	vector_end:
...
```

<br>

실제 핸들러 내용 (/boot/Entry.S)

```c
...
reset_handler:
        MRS r0, cpsr
        BIC r1, r0, #0x1F
        ORR r1, r1, #ARM_MODE_BIT_SVC
        MSR cpsr, r1
        LDR sp, =SVC_STACK_TOP

        MRS r0, cpsr
        BIC r1, r0, #0x1F
        ORR r1, r1, #ARM_MODE_BIT_IRQ
        MSR cpsr, r1
        LDR sp, =IRQ_STACK_TOP

        MRS r0, cpsr
        BIC r1, r0, #0x1F
        ORR r1, r1, #ARM_MODEm_BIT_FIQ
        MSR cpsr, r1
        LDR sp, =FIQ_STACK_TOP

        MRS r0, cpsr
        BIC r1, r0, #0x1F
        ORR r1, r1, #ARM_MODE_BIT_ABT
        MSR cpsr, r1
        LDR sp, =ABT_STACK_TOP

        MRS r0, cpsr
        BIC r1, r0, #0x1F
        ORR r1, r1, #ARM_MODE_BIT_UND
        MSR cpsr, r1
        LDR sp, =UND_STACK_TOP

        MRS r0, cpsr
        BIC r1, r0, #0x1F
        ORR r1, r1, #ARM_MODE_BIT_SYS
        MSR cpsr, r1
        LDR sp, =USRSYS_STACK_TOP
...
```
