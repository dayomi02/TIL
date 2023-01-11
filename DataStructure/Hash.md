
## Hash

해시는 임의의 크기를 가진 데이터를 고정된 데이터의 크기로 변환시키는 것을 말한다. 해시를 사용하여 특정한 배열의 인덱스, 위치, 위치를 입력하고자 하는 데이터의 값을 이용해 저장하거나 찾을 수 있다. 해시를 사용하면 즉시 저장하거나 찾고자 하는 위치를 참조할 수 있으므로 더욱 빠른 속도로 처리할 수 있다.

- ArrayList는 내부 인덱스를 이용하여 검색이 한번에 이루어지기 때문에 빠른 검색속도를 보장하는 반면, 데이터의 추가/삭제 시 많은 데이터가 밀리거나 당겨지기 때문에 많은 시간이 소요된다.
- LinkedList는 추가/삭제 시 인근 노드들의 참조값만 수정해줌으로써 빠른 처리가 가능하지만 데이터를 검색할 경우 해당 노드를 찾기 위해서 처음부터 순회 검색을 해야하기 째문에 데이터의 수가 많아질수록 효율이 떨어지는 구조이다.
- 해시는 이러한 한계를 극복하기 위해 제시된 자료구조이다.

해시는 내부적으로 배열을 사용하여 데이터를 저장하기 때문에 빠른 검색 속도를 지원한다. 또한 데이터 추가/삭제 시 기존의 데이터를 밀어내거나 당기는 작업이 필요없도록 특별한 알고리즘을 이용하여 데이터와 연관된 고유한 숫자를 만들어 낸 뒤 이를 데이터의 인덱스로 사용한다. 이 인덱스를 인덱스에 저장되는 데이터만의 고유한 위치로 정하여서 데이터 추가/삭제 시 데이터의 이동이 없도록 만들어진 구조이다. 

### Hash Table

해시가 내부적으로 사용하는 배열을 Hash Table 이라고 한다. 이는 크기에 따라 성능 차이가 발생할 수 있다. 해시의 key - value 형태 값 중에서 key값을 테이블에 저장할 때 key값을 Hash Method를 이용해서 계산한 뒤, 그 결괏값을 배열의 인덱스로 사용하여 저장한다.

### Hash Method

Hash Table 설명 내용 중 key 값을 생성하여 인덱스로 사용한다고 설명했다. 이때 인덱스를 생성하는 것이 Hash Method이다. Hash Method에 의해 반환된 데이터의 고유 숫자값을 Hash Code라고 한다. Hasj Method를 이용해서 데이터를 Hash Table에 저장하고 검색하는 기법을 해싱(Hashing)이라고 한다. Hash Method는 데이터가 저장되어 있는 곳을 알려주기 때문에 다량의 데이터 중에서도 원하는 데이터를 빠르게 찾을 수 있다.

자바에서는 Object 클래스의 hashCode()메서드를 이용해서 모든 객체의 Hash Code 를 쉽게 구할 수 있다. 

### Hashing

Hash Table을 이용한 탐색을 말한다.

HashMap과 같이 해싱을 구현한 컬렉션 클래스에서는 Object 클래스에 정의된 hashCode()를 Hash Method로 사용한다. hashCode()는 객체의 주소를 이용하는 알고리즘으로 해시 코드를 만들어내기 때문에 모든 객체에 대해 중복되지 않는 해시 코드를 생성한다.

```java
import java.util.HashMap;

String a = "Hello";
String b = "Hello";
System.out.println("a hashCode = "+a.hashCode());
System.out.println("b hashCode = "+b.hashCode());
System.out.println("equals = "+a.equals(b));

//실행 결과
a hashCode = 69609650
b hashCode = 69609650
equals = true
```

HashMap도 hashCode() 메서드를 사용하여 객체를 구별하기 때문에 이미 존재하는 키와 동일한 값을 저장할 경우 새로운 객체로 인식하여 값이 추가되는 것이 아니라, 기존의 값을 새로운 값으로 덮여쓴다.

출처

[https://jroomstudio.tistory.com/10](https://jroomstudio.tistory.com/10)

[https://hsp1116.tistory.com/35](https://hsp1116.tistory.com/35)
