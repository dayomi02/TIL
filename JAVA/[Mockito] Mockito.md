# Mockito

Mockito 는 MIT 라이선스에 따라 출시된 JAVA용 오픈소스 테스트 프레임워크이다. 이 프레임워크를 사용하면 테스트 주도 개발(TDD) 또는 동작 주도 개발(BDD)을 위해 자동화된 단위 테스트에서 테스트 이중 개체(모의 개체)를 만들 수 있다. *(프레임워크의 이름과 로고는 음료의 일종인 모히토에서 따온 것이다…)*

Mockito를 사용하면 개발자가 미리 기대치를 설정하지 않고도 테스트 중인 시스템의 동작을 확인할 수 있다.

오픈소스로 제작되어 mockito github에서 코드를 확인할 수 있다. ([mockito/mockito: Most popular Mocking framework for unit tests written in Java (github.com)](https://github.com/mockito/mockito))

### Mock

한글로 번역하면 ‘가짜의’ 또는 ‘모의의’ 라는 뜻을 갖고 있다. 한 마디로 **객체를 가짜로 만들어서 테스트** 한다는 뜻이다. 이를 통해 필요한 기능에만 단위 테스트 하는 것을 집중하게 해준다.

이러한 객체를 **Mock Object(모의 객체)**라고 한다.

이를 통해서 불필요한 객체를 선언하지 않고 가짜 객체를 만들어 의존 시키게 하여 실제 테스트할 객체를 만들 수 있다. 만약 테스트하려는 메서드가 가짜 객체의 응답을 필요로 한다면 **Stub**이라는 방법을 사용해 테스트를 할 수 있다.

### Stub

**Mock 객체가 가지고 있는 일부 메서드의 기능에 집중해, 해당 메서드의 반환 값을 임의로 지정해주는 행동**이다.

Mock 객체를 만들어주고 이 객체가 할 행동을 stub을 통해 지정해주면 복잡한 단계를 가진 로직도 최소화하여 원하는 기능만 테스트를 할 수 있고, 단위 테스트의 원칙 중 하나 인 ‘다른 테스트에 의존하면 안 된다’ 를 지킬 수 있게 된다.

### Spy

객체 전체를 mocking 하는 방법 말고도 객체의 일부분만 mocking 하는 것을 말한다. mocking 된 부분 말고는 실제 객체와 동일하게 동작한다.

(mocking: 객체를 생성하는 행위)

## 사용하기

SpringBoot 2.2 이상이면 spring-boot-starter-test에 Mockito가 포함되어 있다. 따라서 별도의 의존성 추가 작업 없이 바로 사용할 수 있다.

*jar 아이콘이 흐리게 보이는 이유는 build.gradle 파일에 spring-boot-starter-test가  testImplementation 으로 설정되어 있기 때문이다.*

### Given - When -Then

Given-When-Then 패턴을 이용하여 Mock 테스트를 구성한다.

- Given: 테스트를 위한 준비 과정. 변수를 선언하고, Mock 객체에 대한 정의도 함께 작성.
- When: 테스트를 실행하는 과정. 테스트하고자 하는 내용을 작성.
- Then:  테스트를 검증하는 과정. 예상한 값과 결괏값이 일치하는 지 확인.

출처: [Mockito](https://en.wikipedia.org/wiki/Mockito), [[Test] Mockito를 이용한 단위 테스트](https://velog.io/@wlsh44/symr7p68), [Mockito 알아보기 (부제 : BDD)](https://loopstudy.tistory.com/315), [[Spring] JUnit5, Mockito 이용한 테스트 코드](https://velog.io/@wonizizi99/Spring-JUnit5-Mockito-이용한-테스트-코드)
