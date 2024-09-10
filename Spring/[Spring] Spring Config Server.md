### 배경

- 서버 애플리케이션이 직접 권한 정보를 가지고 있으면 보안 취약점이 발생하게 됨.
- 사용하고자 하는 시스템의 환경 설정 값이 자주 바뀌는 경우가 있을 수 있는데, 그때마다 서버 애플리케이션은 변경된 환경 설정 값을 갱신하여 다시 빌드, 배포를 진행해야 한다.

따라서 보안 적인 측면에서나, 혹은 서버의 운영 측면에서 보면 서버의 환경 설정 정보는 중앙에서 관리하고, 각 서버 애플리케이션에서 관리해주는 것이 매우 좋을 것임. 

이 기능을 지원하는 Spring Framework의 기능 중 하나가 **Spring Colud Config** 이다.

### Spring Colud Config

분산 시스템에서 외부화된 구성에 대한 서버 측 및 클라이언트 측 지원을 제공한다. Config Server응 사용하면 모든 환경에서 애플리케이션의 외부 속성을 중앙에서 관리할 수 있다. 클라이언트와 서버의 개념은 Spring 및 추상화에 동일하게 매핑되므로 Spring  응용 프로그램에 매우 적합하지만 모든 언어로 실행되는 모든 응용 프로그램에서 사용할 수 있다.

⇒ 분산된 환경의 서버에서 환경 설정 정보를 중앙에서 모아 관리를 하는데 도움을 주는 라이브러리이다

구현 순서는 다음과 같다.
Spring colud config server → Spring cloud config client → config 값의 암호화 → repository 연결

* 아래 예제 소스는 eGov 4.2 프로젝트를 기반으로 진행하였음.

### Spring colud config server

의존성 추가

```jsx
    implementation 'org.springframework.boot:spring-boot-starter-actuator'    // bus
    implementation 'org.springframework.cloud:spring-cloud-config-server'
    implementation 'org.springframework.cloud:spring-cloud-config-monitor'    // webhook
```

어노테이션 추가

```java
package org.egovframe.cloud.config;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.config.server.EnableConfigServer;

@EnableConfigServer
@SpringBootApplication
public class ConfigApplication {

    public static void main(String[] args) {
        SpringApplication.run(ConfigApplication.class, args);
    }

}
```

설정 파일

```yaml
# application.yml
server:
  port: 8888

spring:
  application:
    name: config-service
  profiles:
    active: native,default # native file repository
  cloud:
    config:
      server:
        native:
          search-locations: ${search.location:file:///${user.home}/workspace.edu/egovframe-msa-edu/config} # Windows
    bus:
      enabled: true # webhook 활성화: /monitor 엔드포인트 호출 가능해진다
  rabbitmq:
    host: ${rabbitmq.hostname:localhost}
    port: 5672
    username: guest
    password: guest

# config server actuator
management:
  endpoints:
    web:
      exposure:
        include: busrefresh
```

### Spring cloud config client

설정 파일

```yaml
spring:
  cloud:
    config:
      uri: http://localhost:8888
      name: portal-service # portal-service.yml이 있으면 불러오게 된다
#      name: config-service # config-service의 application.yml 을 불러오게 된다
#  profiles:
#    active: prod # application-prod.yml
```

### config 값의 암호화

### 출처

https://cheese10yun.github.io/spring-config-server/

https://velog.io/@18k7102dy/Spring-Cloud-cloud-config에-대한-설명-및-구현

https://docs.spring.io/spring-cloud-config/docs/current/reference/html/
