## IoC

Inversion of Control: 제어 반전

IoC 란, 객체의 생성, 생명주기의 관리까지 모든 객체에 대한 제어권이 바뀌었다는 것을 의미한다.  컴포넌트 의존 관계 설정(Component deoendency resoulution), 설정(Configuration) 및 생명 주기(Life Cycle)을 해결하기 위한 디자인 패턴(Design Pattern)이다.

프로그래머와 프레임워크의 주체가 바뀌었다고 표현한다. 일반적인 경우라면 개발자가 미리 정한 순서에 따라 생성, 실행을 주도하고 의도했다면 IoC 가 등장한 이후는 객체의 생성, 생명주기, 관리까지 모든 객체에 대한 주도권은 프레임워크가 가진 것이다. (제어권이 개발자에서 프레임워크로 반전되었음.)

- IoC를 통해 애플리케이션을 구성하는 객체 간의 낮은 결합도를 유지할 수 있음.
- IoC 의 역할을 담당하는 것이 Spring Container임.
- Spring Container 를 IoC Container 라고도 함.

## Spring container (=IoC Container)

스프링 컨테이너는 Spring Application 내에서 자바 객체를 관리하는 공간을 뜻한다. (Spring에서 자바 객체를 Bean 이라고 부른다)

컨테이너의 역할은 의존성 주입(DI, Dependency Injection) 을 통하여 애플리케이션을 구성하는 Bean 들의 생명 주기를 개발자 대신 관리해준다. (= DI를 통 Bean의 생성, 소멸 관리) Bean들을 관리한다는 의미로 컨테이너를 BeanFactory하고 부른다.

- 객체의 생성과 객체 사이의 런타임 관계를 DI 관점에서 볼 때 컨테이너를 BeanFactory하고 한다.
- BeanFactory에 여러가지 컨테이너 기능을 추가한 애플리케이션 컨텍스트(ApplicationContext)가 있다.

### BeanFactory

- BeanFactory 계열의 인터페이스만 구현한 클래스는 단순히 컨테이너에서 객체를 생성하고 DI를 처리하는 기능만 제공한다.
- Bean 을 등록, 생성, 조회, 반환 관리를 한다.
- Factory 디자인 패턴을 구현한 것으로 BeanFactory는 빈을 생성하고 분배하는 책임을 지는 클래스이다.
- Bean을 조회할 수 있는 getBean() 메서드가 정의되어 있다.
- 보통은 BeanFactory 를 바로 사용하지 않고, 이를 확장한 ApplicationContext를 사요한다.

### ApplicationContext

- Bean 을 등록, 생성, 조회, 반환 관리하는 기능은 BeanFactory와 같다.
- 스프링의 각종 부가 기능을 추가로 제공한다.
    - 국제화가 지원되는 텍스트 메시지를 관리해준다.
    - 이미지같은 파일 자원을 로드할 수 있는 포괄적인 방법을 제공해준다.
    - 리스너로 등록된 빈에게 이벤트 발생을 알려준다.

Spring 공식 문서 상 컨테이너를 사용해야 할 때 특별한 이유가 없다면, ApplicationContext를 사용하라고 권장한다. 그 이유는 BeanFactory(interface) ← ApplicationContext(interface) ← ApplicatioContext(구현체) 의 구조이며, BeanFactory의 모든 기능을 ApplicationContext가 포함하고 있고. 추가 기능까지 있기 때문이다.

출처: [[Spring] Spring-Container, IoC, DI, Singleton 개념 정리](https://lucas-owner.tistory.com/39), [[Spring] IoC 컨테이너 (Inversion of Control) 란?](https://dev-coco.tistory.com/80)
