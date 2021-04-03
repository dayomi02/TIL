# Paginng : Multi-level Page Table
 
## Paging: Linear Tables

페이지 테이블이 너무 커서

**페이지 테이블이 너무 커서 메모리를 너무 많이 소모한다.**

 <br>
 
## Paging: Smaller Tables

**큰 페이지는 내부 단편화로 이어진다.**

 <br>

# Multi-level Page Table

선형 페이지 테이블을 트리처럼 만든다.

- 페이지 테이블을 페이지 크기 단위로 자른다.
- 페이지 테이블 항복의 전체 페이지가 잘못된 경우, 페이지 테이블의 해당 페이지를 할당하지 않는다.
- 페이지 테이블의 페이지가 유효한지 여부를 추적하려면 Page directory 라는 새 구조를 사용해야한다.

 <br>
 
## Page Directory

PFN를 찾아갈 때 Linear page table은 불필요한 페이지까지 사용해야 한다.

하지만 Multi-level page table은 페이지 디렉토리를 조회하고 그 디렉토리 내용을 바탕으로 페이지를 찾아가는 방식으로 불필요한 페이지를 사용하지 않아도 된다.
 
 <br>
 
## Page Directory Entries

페이지 디렉토리는 페이지 테이블의 페이지당 하나의 entry를 포함한다.

여러 page directory entries(PDE)로 구성된다.

PDE에 valid bit(유효한 비트) 및 page frame number(PFN)가 있다.
 
 <br>
 
## Advantage & Disadvantage

Advantage

- 사용 중인 주소 공간의 크기에 비례하여 페이지 테이블 공간만 할당한다.
- OS는 페이지 테이블을 할당하고나 확장해야할 때 다음  free page를 사용할 수 있다.

Disa

- Multi-level table은 time-space trade-off의 예이다.
- 복잡하다.
 
 <br>
 
## Level of Indirection

multi-level 구조는 페이지 디렉토리를 사용하여 간접 수준을 조정할 수 있다.

​	방향은 실제 메모리에서 원하는 위치에 페이지 테이블 페이지를 배치한다.

레벨이 높을 수록 공간 효율이 높아지지만 코드와 구조는 복잡해진다.

 
 <br>
 

## Page Directory Idx

페이지 디렉토리에는 페이지 테이블의 페이지당 하나의 엔트리가 필요하다.

페이지 디렉토리 항목이 잘못되었을 경우 → Raise an exception (액세스가 유효하지 않음)
 
 <br>
 
## Page Table Idx

PDE가 유효할 경우, 더 많은 할 일이 있다.

이 PTE가 가리키는 페이지 테이블의 페이지에서 PTE을 가져온다.

그런 다음 이 페이지 테이블 인덱스를 사용하여 페이지 테이블 자체를 인덱싱할 수 있다.
