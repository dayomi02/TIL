# Paging : Introduction

## Concept of Paging

- 페이지는 주소 공간을 Page라고 하는 고정 크기의 단위로 분할한다.

  - Segmentation : 논리적 세그먼트(code, stack, heap, 등)의 가변 크기

- Paging을 사용하면 **실제 메모리**도 **Page Frame**이라고 하는 페이지 수로 **분할**된다.

- 가상주소를 실제주소로 **변환**하려면 프로세스별 **Page table**이 필요하다.

  
<br>

## Advantages of Paging

- 유연성

   (Flexibility) : 주소 공간의 추상화를 효과적으로 지원

  - 힙과 스택이 어떻게 확장되고 사용되는지 가정할 필요가 없다. (???)

- 단순성

   (Simplicity) : 여유 공간 관리 용이성

  - 주소공간의 Page와 Page Frame의 크기가 같다.
  - 할당이 용이하고 사용 가능한 free list

<br>

## Address Translation

- 가상주소의 두 구성 요소
  - VPN : virtual page number (가상 페이지 번호)
  - Offset : 페이지 내의 오프셋


<br>

## What is in the Page Table?

Page Table은 가상 주소를 실제 주소로 매핑하는 데 사용되는 **자료 구조**일 뿐이다.

간단한 양식 : 선형 페이지 테이블, 배열

OS는 VPN을 기준으로 Array를 **인덱싱**하고 Page Table 항목을 검색한다.
