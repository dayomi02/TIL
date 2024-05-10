# [Mockito] static 메서드 Mockito 사용하기
**static 메서드 Mockito 사용하기**

```java
String html = HtmlExtractor.extractHtml(targetUrl);

// targetUrl 홈페이지의 html 요소를 가져오는 소스코드.
// 해당 로직은 외부 요인에 영항을 받는 로직. 따라서 테스트 진행 시 해당 로직을 신경쓰지 않고 테스트해야함.
```

Mockito을 사용하여 위와 같은 소스 코드를 테스트하기 위해서는 `HtmlExtractor` 클래스의 `extractHtml` 메서드가 정적(static)이 아니어야 한다. Mockito는 정적 메서드를 모의(mock)할 수 없기 때문이다.

따라서 `HtmlExtractor` 클래스의 `extractHtml`가 정적이 아니라면, Mockito를 사용하여 해당 메서드를 아래와 같이 mocking 할 수 있다. 

```java
Mockito.when(HtmlExtractor.extractHtml(Mockito.anyString(), Mockito.anyString()))
      .thenReturn("모의된 HTML 내용");
```

위의 코드에서는 `extractHtml`메서드가 문자열 두 개를 인수로 받는다고 가정한 것이다.

하지만 만약 `extractHtml`메서드가 static(정적) 메서드라면 Mockito로 mocking 할 수 없다. 이 경우에는 테스트 대역(Test Double) 패턴 중 하나인 Spy를 사용하거나 다른 방법을 고려해야 한다.

**PowerMockito**

PowerMockito는 Mockito와 함께 사용되는 Mockito 확장 라이브러리로, static 메서드와 같은 테스트하기 어려운 대상들을 mocking 할 수 있다. PowerMockito를 사용하면 static 메서드도 mocking할 수 있다. 

```java
import org.powermock.modules.junit4.PowerMockRunner;
import org.powermock.modules.junit4.PowerMockRunnerDelegate;
import org.powermock.core.classloader.annotations.PrepareForTest;
...

@PowerMockRunnerDelegate(PowerMockRunner.class)
@PrepareForTest({HtmlExtractor.class})
public class TestClass {

    @Test
    public void testMethod() {
        ...
        Mockito.mockStatic(HtmlExtractor.class);
		    Mockito.when(HtmlExtractor.extractHtml(Mockito.anyString(), Mockito.anyString()))
          .thenReturn(html);

        ...
    }
}
```

PowerMockito를 사용하여 static 메서드를 mocking하기 위해 클래스에 `@RunWith(PowerMockRunner.class)`와 `@PrepareForTest({SeleniumHtmlExtractor.class})`를 추가하였다. PowerMockito 관련 어노테이션을 사용하기 위해서는 의존성을 추가해야 한다.

```xml
dependencies {
    testImplementation group: 'junit', name: 'junit', version: '4.12'
    testImplementation "org.powermock:powermock-module-junit4:1.6.6"
    testImplementation "org.powermock:powermock-api-mockito:1.6.6"
}
```

순서대로 JUnit v4.12, PowerMock v1.6.6, 그리고 PowerMock v1.6.6과 호환되는 Mockito 버전(작성 기준 v1.10.19)으로 설정하면 된다.

출처: openai chat gpt 3.5, [PowerMock 사용하기 1](https://bestalign.github.io/dev/intro-powermock-1/)
