# Spring AOP

2024.05.07(화)

## AOP(Aspect-Oriented Programming)

AOP 는 관점(Aspect) 지향 프로그래밍으로, 관점을 기준으로 다양한 기능을 분리하여 보는 프로그래밍이다. 즉 소스 코드 상에서 각각의 관점을 핵심적인 관점과, 부가적인 관점으로 나누어보고 그 관점을 기준으로 각각 분리하는 것을 의미한다.

<aside>
💡 관점(Aspect): 부가 기능과 그 적용처를 정의하고 합쳐서 모듈로 만든 것.

</aside>

### **AOP의 목적**

관점 지향 프로그래밍은 객체 지향 프로그래밍을 보완하기 위해 쓰인다. 기존 객체 지향은 목적에 따라 클래스를 만들고 객체를 만들었다. 따라서 핵심 비즈니스 로직이나 부가 기능의 로직을 하나의 객체로 분리하는데 그친다. 그래서 이 기능들을 어떻게 바라보고 나누어 쓸 지에 대한 정의가 부족하다는 단점이 있다.

보통 비즈니스 웹 애플리케이션이라면 사업에 핵심적인 핵심 비즈니스 로직이 있고, 애플리케이션 전체를 관통하는 부가 기능 로직이 있다. 이를 횡단 관심사(cross-cutting concerns)라고 한다.

**횡단 관심사의 코드를 핵심 비즈니스 로직의 코드와 분리하여 코드의 간결성을 높이고 변경에 유연함과 무한한 확장이 가능하도록 하는 것**이 AOP의 목적이다.

<aside>
💡 **횡단 관심사**(Corsscutting Concerns): 핵심적인 기능이 아닌 중간 중간에 삽입되어야 할 기능들 관심들을 말한다. 로킹, 보안, 트랜잭션 처리 등이 있다.

</aside>

### AOP 적용 방식

- **컴파일 시점 적용**
    
    컴파일 시점 적용 방식은 AspectJ 컴파일러가 일반 `.java` 파일을 컴파일할 때 부가 기능을 넣어서 `.class` 파일로 컴파일해주는 것을 의미한다. 이 동작을 Aspect와 실제 코드를 연결하는 **위빙(weaving)**이라고 부른다.
    
- **클래스 로딩 시점 적용**
    
    JVM 내 클래스 로더에 `.class` 파일을 올리는 시점에 바이트 코드를 조작해 부가 기능 로직을 추가하는 방식이다.
    
- **런타임 시점 적용**
    
    컴파일, 클래스 로딩, main 메서드의 실행 이후에 자바가 제공하는 범위 내에 부가 기능을 적용하는 방식이다. 이미 런타임 중이라 코드를 조작하기 어려워 스프링 컨테이너, DI, Bean 등 여러 개념과 기능을 총동원하여 **프록시를 통해 부가 기능을 적용**하는 방식이다.
    
    프록시는 메서드 실행 시점에서만 다음 타겟을 호출할 수 있기 때문에, **런타임 시점에 부가 기능을 적용하는 방식은 메서드의 실행 지점으로 제한**된다.
    

## Spring AOP

Spring AOP는 런타임 시점에 적용하는 방식을 사용한다. 이유는 컴파일 시점과 클래스 로딩 시점에 적용하려면 별도의 컴파일러와 클래스로더 조작기를 써야 하는데, 이것을 정하고 사용 및 유지하는 과정이 매우 어렵고 복잡하기 때문이다.

**용어 및 개념**

- **Aspect**
    
    공통 기능. Advice + Pointcut 을 모듈화 한 애플리케이션의 횡단 기능.
    
- **Join Point**
    
    애플리케이션 실행 흐름에서의 특정 포인트. (클래스 초기화, 메서드 호출, 예외 발생 등) AOP를 적용할 수 있는 모든 지정 (스프링에서는 메서드 실행 지점으로 제한)
    
- **Advice**
    
    Join Point에서 실행되는 코드. 즉 부가 기능 그 자체. Aspect를 언제 핵심 코드에 적용할지 정의.
    
    | 타입 | 설명 |
    | --- | --- |
    | Before | Join Point 실행 이전에 실행. 일반적으로 리턴 타입 void. |
    | After returning | Join Point 실행 완료 후 실행. (메서드가 예외 없이 실행될 때) |
    | After Throwing | 메서드가 예외를 던지는 경우 실행. |
    | After (finally) | Join Point의 동작과 관계없이 실행. |
    | Around | 메서드 호출 전후에 수행(Join Point 실행 여부 선택, 반환 값 변환, 예외 변환, try~catch~finally 구문 처리 가능 등), 가장 강력한 Advice 임. |
- **Pointcut**
    
    Join Point 중 Advice가 적용될 지점을 선별하는 기능. 주로 AspectJ 표현식으로 지정.
    
- **Target**
    
    핵심 기능을 담은 모듈. (= 부가 기능 부여 대상) Advice를 받는 객체이고, Pointcut으로 결정됨.
    
- **Advisor**
    
    Sprint AOP에서만 쓰는 용어로, 하나의 Advice와 하나의 Pointcut으로 구성된 Aspect를 특별하게 지칭하는 말.

[[Spring] Spring AOP 개념](https://velog.io/@kai6666/Spring-Spring-AOP-개념) <p>
[AOP란? 횡단 관심사? 흩어진 관심사?](https://willseungh0.tistory.com/61)
