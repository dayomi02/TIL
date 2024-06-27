## PMD?

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/256fca12-b5f2-4de6-a291-a0cdf28524ad/Untitled.png)

PMD란 응용 프로그램 코드에서 발견된 문제를 보고하는 오픈 소스 정적 분석 도구 (JAVA 소스 코드 분석기) 이다. 

미사용 변수, 비어있는 코드 블럭, 불필요한 오브젝트 생성과 같은 결함을 유발할 수 있는 코드를 검사한다. 일반적으로 시큐어 코딩을 위해 자바 코드를 검사해서 나쁜 코딩을 잡아주고 그에 대한 설명을 지원한다. 

PMD에는 기본으로 제공하는 RuleSet이 포함되어 있으며 사용자 지정 규칙을 작성할 수 있다.

대표적으로 아래와 같은 소스 코드의 결함을 감지할 수 있다.

- try / catch / finally / switch 블록이 비어 있을 때
- if / while 문이 비어 있을 때
- 불필요한 if 문일 때
- 낭비적인 string / stringbuffer 를 사용하고 있을 때
- 복사 / 붙여 넣기를 많이 해 유지 관리 능력을 떨어뜨릴 때 등

[PMD](https://pmd.github.io/)

## PMD 사용 방법

[Documentation Index | PMD Source Code Analyzer](https://docs.pmd-code.org/latest/)

사용자 문서

### 1. PMD 설치 및 설정

[](http://pmd.github.io/latest/pmd_download.html)

PMD는 zip 압축 파일로 배포된다. 공식 github 홈페이지에서 최신 배포판을 다운로드 받을 수 있다.

PMD 공식 홈페이지에서 PMD 파일을 다운로드 받고, 적절한 위치에 압축 해제한다.

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/922dcc26-3edc-457d-8e77-fc12a09559b6/Untitled.png)

압축 해제한 경로에 맞게 환경 변수를 생성한다.

시스템 환경 변수 편집 > 시스템 속성 > 환경 변수 > 시스템 변수 > “Path” 클릭 > 새로 만들기 >  `*path_to_pmd*/bin/` 추가 후 저장

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/8b5742ba-0ac8-45dd-9b63-9fa47178d3cb/Untitled.png)

정상적으로 설치되었는지 확인한다.

```bash
pmd --version
```

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/436fca60-e1c4-434f-9958-d3e55fa5accf/Untitled.png)

### 2. PMD 실행

사용할 ruleset을 생성한다. 

pmd github에서 제공하는 quickstart.xml을 사용하였다. ruleset 작성 관련한 자세한 내용은 공식 홈페이지 참고.

https://github.com/pmd/pmd/blob/master/pmd-java/src/main/resources/rulesets/java/quickstart.xml

[Making rulesets | PMD Source Code Analyzer](https://docs.pmd-code.org/latest/pmd_userdocs_making_rulesets.html)

pmd 실행.

```bash
 pmd check -d ..\..\..\src\main\java -f text -R rulesets/java/quickstart.xml > pmd_result\pmd_report.txt
```

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/aaaa9d5e-da8a-4794-9274-e82a9ed7badf/Untitled.png)

위 명령어의 각 옵션의 설명은 아래와 같다.

- **`pmd check`**: PMD 도구를 실행하는 명령어
- **`-d ..\..\..\src\main\java`**: 분석할 Java 소스 코드의 디렉토리를 지정하는 옵션
- **`-f text`**: PMD가 생성할 결과 파일의 형식을 지정하는 옵션
    - -f
        
        **text**: 단순한 텍스트 형식으로 출력합니다.
        **xml**: XML 형식으로 출력합니다. 다양한 도구에서 쉽게 파싱하고 처리할 수 있습니다.
        **csv**: CSV(쉼표로 구분된 값) 형식으로 출력합니다. 스프레드시트 애플리케이션에서 쉽게 열 수 있습니다.
        **emacs**: Emacs 편집기에서 사용할 수 있는 형식으로 출력합니다.
        **summaryhtml**: 요약된 HTML 보고서를 생성합니다.
        **html**: HTML 형식으로 출력합니다. 브라우저에서 쉽게 볼 수 있는 형태로 출력됩니다.
        **json**: JSON 형식으로 출력합니다. 다양한 프로그래밍 언어에서 쉽게 파싱할 수 있습니다.
        **ideaj**: IntelliJ IDEA에서 사용할 수 있는 형식으로 출력합니다.
        **textcolor**: 터미널에서 컬러 출력을 지원하는 텍스트 형식으로 출력합니다.
        **sarif**: SARIF (Static Analysis Results Interchange Format) 형식으로 출력합니다. 정적 분석 도구의 결과를 교환하기 위한 표준 형식입니다.
        
- **`-R rulesets/java/quickstart.xml`**: 사용할 PMD 규칙 세트를 지정하는 옵션
- **`> pmd_result\pmd_report.txt`**: 분석 결과를 저장할 파일의 경로를 지정하는 리다이렉션(redirect) 명령

pmd 명령어 실행 결과 설정한 파일로 분석 결과가 저장된 것을 확인할 수 있다.

```
..\..\..\src\main\java\com\study\opensearch\DemoApplication.java:9:	UseUtilityClass:	This utility class has a non-private constructor
..\..\..\src\main\java\com\study\opensearch\batch\BatchRunnerConfig.java:3:	UnnecessaryImport:	Unused import 'com.study.opensearch.util.Constants'
..\..\..\src\main\java\com\study\opensearch\batch\BatchRunnerConfig.java:4:	UnnecessaryImport:	Unused import 'com.study.opensearch.util.OpenSearchClientManager'
..\..\..\src\main\java\com\study\opensearch\batch\BatchRunnerConfig.java:9:	UnnecessaryImport:	Unused import 'org.springframework.batch.core.JobParameters'
..\..\..\src\main\java\com\study\opensearch\batch\BatchRunnerConfig.java:10:	UnnecessaryImport:	Unused import 'org.springframework.batch.core.JobParametersBuilder'
..\..\..\src\main\java\com\study\opensearch\batch\BatchRunnerConfig.java:14:	UnnecessaryImport:	Unused import 'org.springframework.boot.CommandLineRunner'
..\..\..\src\main\java\com\study\opensearch\batch\BatchRunnerConfig.java:15:	UnnecessaryImport:	Unused import 'org.springframework.context.annotation.Bean'
..\..\..\src\main\java\com\study\opensearch\batch\BatchRunnerConfig.java:16:	UnnecessaryImport:	Unused import 'org.springframework.scheduling.annotation.Scheduled'
..\..\..\src\main\java\com\study\opensearch\batch\BatchRunnerConfig.java:19:	UnnecessaryImport:	Unused import 'java.io.File'
..\..\..\src\main\java\com\study\opensearch\batch\BatchRunnerConfig.java:20:	UnnecessaryImport:	Unused import 'java.io.FilenameFilter'
..\..\..\src\main\java\com\study\opensearch\batch\BatchRunnerConfig.java:21:	UnnecessaryImport:	Unused import 'java.io.IOException'
..\..\..\src\main\java\com\study\opensearch\batch\BatchRunnerConfig.java:22:	UnnecessaryImport:	Unused import 'java.time.LocalDateTime'
..\..\..\src\main\java\com\study\opensearch\batch\BatchRunnerConfig.java:23:	UnnecessaryImport:	Unused import 'java.time.format.DateTimeFormatter'
..\..\..\src\main\java\com\study\opensearch\batch\ManageLogJobConfig.java:43:	GuardLogStatement:	Logger calls should be surrounded by log level guards.
..\..\..\src\main\java\com\study\opensearch\batch\ManageLogJobConfig.java:58:	GuardLogStatement:	Logger calls should be surrounded by log level guards.
..\..\..\src\main\java\com\study\opensearch\batch\ManageLogJobConfig.java:74:	GuardLogStatement:	Logger calls should be surrounded by log level guards.
..\..\..\src\main\java\com\study\opensearch\batch\ManageLogJobConfig.java:95:	GuardLogStatement:	Logger calls should be surrounded by log level guards.
..\..\..\src\main\java\com\study\opensearch\batch\ManageLogJobConfig.java:110:	GuardLogStatement:	Logger calls should be surrounded by log level guards.
..\..\..\src\main\java\com\study\opensearch\batch\ManageLogJobConfig.java:138:	GuardLogStatement:	Logger calls should be surrounded by log level guards.
..\..\..\src\main\java\com\study\opensearch\batch\ManageLogJobConfig.java:154:	GuardLogStatement:	Logger calls should be surrounded by log level guards.
..\..\..\src\main\java\com\study\opensearch\batch\MongoToBulkJsonJobConfig.java:114:	UnnecessaryLocalBeforeReturn:	Consider simply returning the value vs storing it in local variable 'bulkItem'
..\..\..\src\main\java\com\study\opensearch\batch\MongoToBulkJsonJobConfig.java:143:	GuardLogStatement:	Logger calls should be surrounded by log level guards.
..\..\..\src\main\java\com\study\opensearch\batch\MongoToJsonJobConfig.java:15:	UnnecessaryImport:	Unused import 'org.springframework.batch.item.ItemProcessor'
..\..\..\src\main\java\com\study\opensearch\batch\OpenSearchBatchJobConfig.java:5:	UnnecessaryImport:	Unused import 'com.study.opensearch.util.*'
..\..\..\src\main\java\com\study\opensearch\batch\OpenSearchBatchJobConfig.java:9:	UnnecessaryImport:	Unused import 'org.apache.http.HttpHost'
..\..\..\src\main\java\com\study\opensearch\batch\OpenSearchBatchJobConfig.java:11:	UnnecessaryImport:	Unused import 'org.apache.http.client.HttpClient'
..\..\..\src\main\java\com\study\opensearch\batch\OpenSearchBatchJobConfig.java:15:	UnnecessaryImport:	Unused import 'org.apache.http.impl.client.HttpClientBuilder'
..\..\..\src\main\java\com\study\opensearch\batch\OpenSearchBatchJobConfig.java:19:	UnnecessaryImport:	Unused import 'org.opensearch.action.bulk.BulkRequest'
..\..\..\src\main\java\com\study\opensearch\batch\OpenSearchBatchJobConfig.java:20:	UnnecessaryImport:	Unused import 'org.opensearch.action.bulk.BulkResponse'

```

### 3. 결과 해석

- 분석 결과를 text 파일 형식으로 제공한다. 이 파일을 통해 코드에서 발견된 문제들을 확인하고 개선할 수 있는 방안을 모색할 수 있다.
- 사용하지 않는 import 문입니다.
    
    ```
    ..\..\..\src\main\java\com\study\opensearch\batch\BatchRunnerConfig.java:14:	UnnecessaryImport:	Unused import 'org.springframework.boot.CommandLineRunner'
    ..\..\..\src\main\java\com\study\opensearch\batch\BatchRunnerConfig.java:15:	UnnecessaryImport:	Unused import 'org.springframework.context.annotation.Bean'
    ..\..\..\src\main\java\com\study\opensearch\batch\BatchRunnerConfig.java:16:	UnnecessaryImport:	Unused import 'org.springframework.scheduling.annotation.Scheduled'
    ..\..\..\src\main\java\com\study\opensearch\batch\BatchRunnerConfig.java:19:	UnnecessaryImport:	Unused import 'java.io.File'
    ```
    
- 반환하기 전에 값을 변수에 저장할 필요가 없습니다. 변수 bulkItem을 간단히 반환하는 것이 더 좋습니다.
    
    ```
    ..\..\..\src\main\java\com\study\opensearch\batch\MongoToBulkJsonJobConfig.java:114:	UnnecessaryLocalBeforeReturn:	Consider simply returning the value vs storing it in local variable 'bulkItem'
    ```
    

### 4. with Intellij

PMD는 Eclipse, IntelliJ IDEA 등에서 PMD 플러그인을 설치하여 IDE 내에서 바로 코드 분석 및 결과를 확인할 수 있다.

intellij 기준으로 설명.

File > Settings > “PMD” 검색 후 install > IDE 재시작

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/6e343c6b-a87a-4d95-a9b1-b1ae912390d4/Untitled.png)

PMD 분석 실행. Tools > Run PMD > Pre Defined > All 

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/cea093c2-37e4-4e99-8324-8f511cabb5ed/Untitled.png)

실행 결과 화면.

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/8f39a42c-9ec0-407f-8d9f-5aa9408d5648/Untitled.png)

사용자가 추가로 RuleSet을 등록하여 사용할 수 있다. 

Settings > Other Settings > PMD > +

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/4718e302-d148-4210-95dd-01953fc76af7/Untitled.png)

## **PMD vs SonarLint**

PMD와 SonarLint는 둘 다 소프트웨어 개발 분야에서 사용되는 정적 분석 도구이다. 두 가지 도구 모두 코드 품질을 향상 시키고 버그를 줄이는 데 도움을 주지만 두 도구 사이에 몇 가지 주요 차이점이 있다.

### Analysis Coverage

PMD는 주로 프로젝트의 소스 코드를 분석하는 데 초점을 맞추는데 반면, SonarLint는 소스 코드를 분석할 뿐만 아니라 MXL 및 속성 파일과 같은 다른 영역의 코드 문제를 확인한다.

SonarLint의 넓은 분석 범위는 보다 포괄적인 코드 검토를 가능하게 한다.

### Integration

PMD는 일반적으로 독립 실행형 도구로서 프로젝트의 빌드 프로세스에 통합되며, 코드 컴파일 후 외부에서 실행된다. 반면, SonarLint는 Eclips, Visual Studio와 같은 IDE를 위한 플러그인을 제공하여 개발자들이 별도의 도구나 빌드 프로세스 통합 없이 개발 중에 실시간 피드백을 받을 수 있도록 한다.

### Language Support

PMD는  Java, JavaScript, XML 등 다양한 프로그래밍 언어를 지원한다. 반면에 SonarLint는 Java 뿐만 아니라 C#, Python, JavaScript 등을 포괄하는 광범위한 언어 지원을 가지고 있다.

**따라서 SonarLint가 여러 프로그래밍 언어 프로젝트에 더 유용하게 사용된다.**

### Rule Configuration

PMD는 개발자가 요구 사항에 따라 활성화하거나 비활성화 할 수 있는 미리 정의된 규칙을 제공한다. 반면 SonarLint은 미리 구성된 규칙을 제공할 뿐만 아니라 개발자가 특정 프로젝트 요구 사항에 맞춘 사용자 정의 규칙을 정의할 수 있도록 한다.

**SonarLint는 PMD 보다 개발자에게 코드 분석 프로세스에 대한 더 많은 제어권을 제공한다고 볼 수 있다.**

### Feedback Mechanism

PMD는 콘솔 출력 또는 생성된 보고서를 통해 피드백을 제공하므로 개발자가 수동으로 결과를 분석해야 한다.

SonarLint는 IDE 통합 기능을 통해 IDE 자체 내에서 즉각적인 피드백을 제공한다.

**SonarLint를 사용하면 코드 편집기에서 코드 문제를 직접 강조하여 개발자가 문제를 더 쉽고 편리하게 식별하고 해결할 수 있다.**

### Continuous Monitoring

SonarLint는 SonarQube 서버와 연결할 수 있으며, 이를 통해 코드 품질을 중앙 집중적으로 관리할 수 있다. 이는 코드 분석 결과를 시간에 따라 저장하고 모니터링 할 수 있어 코드 품질에 대한 과거 데이터와 추세를 제공한다는 것을 의미한다.

PMD는 독립형 도구로서 지속적인 모니터링을 위한 내장된 지원이 없다.

|  | PMD | SonarLint |
| --- | --- | --- |
| 분석 범위 | 주로 프로젝트의 소스 코드를 분석하는 데 초점을 맞춘다.
 | 소스 코드를 분석할 뿐만 아니라 MXL 및 속성 파일과 같은 다른 영역의 코드 문제를 확인한다. SonarLint의 넓은 분석 범위는 보다 포괄적인 코드 검토를 가능하게 해준다. |
| 지원 언어 | Java를 중심적으로 JavaScript, XML 등 다양한 프로그래밍 언어를 지원한다.  | Java 뿐만 아니라 C#, Python, JavaScript 등을 포괄하는 광범위한 언어 지원을 가지고 있다. |
| 피드백 메커니즘 | 콘솔 출력 또는 생성된 보고서를 통해 피드백을 제공하므로 개발자가 수동으로 결과를 분석해야 한다. | IDE 통합 기능을 통해 IDE 자체 내에서 즉각적인 피드백을 제공한다. |
| 지속적인 모니터링 | 독립형 도구로서 지속적인 모니터링을 위한 내장된 지원이 없다. | SonarQube 서버와 연결할 수 있으며, 이를 통해 코드 품질을 중앙 집중적으로 관리할 수 있다. 이는 코드 분석 결과를 시간에 따라 저장하고 모니터링 할 수 있어 코드 품질에 대한 과거 데이터와 추세를 제공한다는 것을 의미한다. |

<aside>
📌 PMD와 SonarLint는 모두 코드 분석을 위한 도구이지만 분석 범위, 통합 옵션, 언어 지원, 규칙 구성 유연성, 피드백 매커니즘, 지속적인 모니터링 능력 등에서 차이가 있다.
두 가지 도구 중 선택은 개발 팀의 구체적인 요구와 선호에 따라 다르게 선택하면 된다.

</aside>

## 출처

[[PMD] 시큐어 코딩을 위한 PMD-eclipse-plugin 사용 방법. (tistory.com)](https://string.tistory.com/43), [PMD 대 SonarLint | 차이점은 무엇입니까? (stackshare.io)](https://stackshare.io/stackups/pmd-vs-sonarlint), [[기타] Intellij PMD로 코드 분석하기 :: 고양멍멍이 (tistory.com)](https://nato-blog.tistory.com/121)
