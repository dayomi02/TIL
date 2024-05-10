# [Mockito] Mockito 메서드 넘기기
### Parameterized Tests

매개변수화 된 테스트는 다른 인수를 사용하여 테스트를 여러 번 실행할 수 있게 한다. 일반적인 `@Test` 메서드와 마찬가지로 선언되지만 `@ParameterizedTest` 주석을 사용한다. 각 호출에 대한 인수를 적어도 하나의 소스로 선언한 뒤 메서드에서 선언한 인수를 사용해야 한다.

아래 소스코드는 `@ValueSource` 주석을 사용하여 문자열 배열을 인수로 지정하는 테스트이다. 아래와 같이 매개변수화 된 테스트를 실행할 때, 각 인자에 대한 호출은 개별적으로 진행될 것이다.

**`@ValueSource`**는 가장 간단한 매개변수화 된 테스트 중 하나 이다. literal 값의 단일 배열을 지정할 수 있으며 테스트 호출 당 단일 인수를 제공하는 데에만 사용할 수 있다. (short, byte, int, float, java.lang.String, java.lang.Class 등의 literal 값을 지원함.)

```java
@ParameterizedTest
@ValueSource(strings = { "racecar", "radar", "able was I ere I saw elba" })
void palindromes(String candidate) {
    assertTrue(StringUtils.isPalindrome(candidate));
}
```

아래는 테스트 코드 작성 실습 도중 작성한 소스 코드이다. 

테스트가 필요한 로직 중  WorkRepository의 WorkProcessor가 가지고 있는 PublishDate 값을 가져오는 로직을 Stub으로 정의하고자 하였다. 해당 로직은 데이터베이스에 저장되어 있는 데이터, 즉 사용할 데이터의 PublishDate 값을 가져오는 로직이라 테스트 작업에 영향이 있는 작업이다. (데이터베이스 연결이 끊길 경우 테스트 작업에 영향이 있음.) 그렇기 때문에 workRepository를 Mock으로 생성한 뒤 해당 작업을 수행하도록 정의(Stubing) 하고자 하였다.

```java
workRepository.getWorkProcessor().getPublishDate();
```

`WorkRepository` 와 `WorkProcessor` 구조이다. 

```java
@Getter
@Component
public class WorkRepository {

  @Autowired
  private WorkProcessor workProcessor;
  ...
}
```

작성한 테스트 메서드이다. 테스트 메서드에 파라미터로 @ParameterizedTest와 @MethodSource를 추가했다. @ParameterizedTest는 매개변수화 된 테스트를 진행하겠다는 의미이고, @MethodSource("invalidRecipeProvider")는 매개변수로 invalidRecipeProvider 메서드의 반환값을 사용하겠다는 의미이다.

`invalidRecipeProvider()` 메서드는 `Stream<Arguments>` 타입의 객체를 반환하며, 각각의 `Arguments` 객체는 하나의 테스트 케이스에 대한 매개변수를 포함한다.

해당 메서드의 매개변수로 `WorkRepository` 객체를 전달하고자 하기 때문에, `WorkRepository` 객체를 인자로 받는 테스트 케이스에 대한 매개변수를 생성하였다.

추가로 나는 `WorkRepository` 객체의 메서드 호출을 해야 하기 때문에 메서드 호출에 대한 동작을 설정하였다. (`provideWorkRepositoryMock()`)

```java
  @ParameterizedTest    
  @MethodSource("invalidRecipeProvider")
  public void test(WorkRepository workRepository) {
  
  }
  
  private static Stream<Arguments> invalidRecipeProvider() {
    WorkRepository workRepositoryMock = provideWorkRepositoryMock();

    return Stream.of(Arguments.of(workRepositoryMock));
  }
  
  public static WorkRepository provideWorkRepositoryMock() {

    WorkRepository workRepositoryMock = mock(WorkRepository.class);

    // getWorkProcessor() 메서드가 null을 반환하지 않도록 설정
    WorkProcessor workProcessorMock = mock(WorkProcessor.class);
    Mockito.when(workRepositoryMock.getWorkProcessor())
        .thenReturn(workProcessorMock);

        return workRepositoryMock;
  }
```

정리해보면 `test()` 메서드의 테스트가 실행될 때 매개변수로 `invalidRecipeProvider()` 메서드가 반환하는 `WorkRepository` Mcok 객체를 사용한다.

출처: openai chat gpt 3.5, [JUnit 5 User Guide](https://junit.org/junit5/docs/current/user-guide/#writing-tests-parameterized-tests)
