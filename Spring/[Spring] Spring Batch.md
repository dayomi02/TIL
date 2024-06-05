# Spring Batch
## 배치(Batch) ?

배치 작업은 **데이터를 실시간으로 처리하는 게 아니라, 일괄적으로 모아서 처리하는 작업을 의미한다.** 

일정 시간마다 개발자가 로직이 동작 되도록 할 수 없기 때문에 배치 작업을 만들게 되고 해당 배치 작업은 매번 정해진 시간마다 동작 되어 다른 부가적인 요소 없이 로직이 처리되도록 한다.

배치를 만들 수 있는 것들은 다양하게 존재한다. 대표적으로 AWS 의 [AWS Batch](https://aws.amazon.com/ko/batch/)가 있다. 이 외에 Spring 진영에서는 Spring Batch라는 것이 있다.

**Spring Batch 에서는 어떤 작업이 수행되어야 한다는 Job 을 정의하고, 생성된 Job 을 일정 주기마다 동작될 수 있도록 Scheduler 에 등록**할 수 있다.

이러한 기능을 통해 부가적인 요소 없이 우리가 원하는 시간마다 동일한 동작을 수행할 수 있도록 설정할 수 있다.

---

## Spring Batch ?

SpringBatch는 Spring에서 작업해야 하는 **대용량 처리들을 반복적으로 수행할 수 있도록 도와주는 배치 프레임워크**이다.

대용량 데이터를 처리하는 경우나 주기적인 업무 일관 처리 등에 사용한다.

SpringBatch는 배치 작업을 트랜잭션으로 관리하고, 실패 시 복구 및 재시작할 수 있는 기능을 제공한다.

### Features

- Transaction Management - 트랜잭션 관리
- Chunk based processing - 청크 기반 처리
- Declarative I/O - 선언형 I/O
- Start/Stop/Restart
- Retry/Skip
- Web based administration interface - 웹 기반 관리 인터페이스

### 사용 목적

| 목적 | 설명 |
| --- | --- |
| 대용량 데이터 처리 | 대규모 데이터베이스, 로그 파일, CSV 파일 등에서 데이터 추출 및 처리를 위해 사용. |
| 자동화된 작업 처리 | 스케줄러를 이용하여 주기적으로 반복되는 작업의 자동 처리를 위해 사용. |
| 분산 처리 | 여러 서버에서 대량의 데이터 처리 가능을 위해 사용. |
| 재시도 및 로깅 | 데이터 처리 중 오류 발생 시 자동 재시도 및 로깅 기능 지원을 위해 사용. |
| 데이터 분석 | 데이터 마이그레이션, 백업 및 복원, 데이터 분석 등 다양한 용도로 사용. |

### 주요 기능

- **Job 과 Step 을 이용한 배치 프로세스 구현** 
배치 처리의 단위 작업(Job)과 작은 단위 작업(Step)을 이용하여 배치 프로세스를 구현하는 기능을 제공한다.
- **Chunk 지향 처리 방식을 통한 대용량 데이터 처리**
Chunk 단위로 데이터를 처리하여 대용량 데이터 처리 기능을 제공한다.
- **Quartz, Cron 등의 스케줄러를 이용한 배치 작업 스케줄링**
스케줄러를 이용하여 배치 작업을 주기적으로 실행하도록 스케줄링을 제공한다.
- **Batch 작업에 대한 로깅과 예외 처리 기능 제공**
Batch 작업 수행 중 로깅과 예외 처리를 지원하여 안정적인 배치 작업을 제공한다.

## Spring Batch Processes and Terms ?

### Process

1. Job Launcher 로 Job 을 실행한다. (Job Launcher → Job)
2. Job은 Step을 통해 실제 배치 처리를 수행한다. (Job → Step) (1:N)
3. Step 에서는 읽어오고, 처리하고, 저장을 수행한다. (Strep → Item Reader, Processor, Writer) (1:1)

### Trems

1. **Job**
    
    **Job은 배치 처리의 단위를 정의하는 최상위 엔티티이다.** 하나의 Job은 여러 개의 Step으로 구성된다.
    
    ***Job Metadata***
    - JobParameters: Job을 실행하는 데 필요한 파라미터
    - JobInstance: Job의 실행 인스턴스
    - JobExecution: Job의 실행 상태 및 결과
    
2. **Step**
    
    **Step은 Job의 세부 작업 단위로, 실제 비즈니스 로직이 실행되는 곳이다.** 각 Step은 독립적으로 실행된다. 
    
    **Tasklet** 또는 **Chunk** 중 하나의 방식을 선택하여 배치 작업을 수행한다.
    
    ***Step Component***
    - ItemReader: 데이터 소스에서 데이터를 읽어오는 역할을 한다.
    - ItemProcessor: 읽어온 데이터를 가공하거나 변환하는 역할을 한다.
    - ItemWriter: 가공된 데이터를 원하는 위치에 기록하는 역할을 한다.
    
3. **JobRepository**
    
    **Job 과 Step의 실행 상태와 메타 데이터를 저장하고 관리하는 역할을 한다.** JobExecution, StepExecution 등의 정보를 데이터베이스에 저장하여 트랜잭션 관리와 실패 복구를 가능하게 한다.
    
4. **JobLauncher**
    
    **Job을 실행시키는 역할을 한다.** Job과 JobParameters를 받아서 JobExecution을 시작하고 관리한다.
    
5. **JobConfiguration**
    
    **Job을 구성하는 설정 파일**로, 스프링 배치에서는 주로 XML이나 자바 Config 클래스로 작성된다. 이 설정 파일에서 Job, Step, ItemReader, ItemProcessor, ItemWriter 등을 정의하고 연결한다.
    

## Spring Batch 개념 정리

### Meta Data DB Schema

- SpringBatch의 실행 및 관리를 위한 목적으로 여러 도메인들(Job, Step, JobParameters 등)에 대한 정보를 저장, 업데이트, 조회 등의 작업을 할 수 있는 스키마
- 과거 및 현재의 배치 실행에 대한 정보(성공, 실패 여부)를 관리함으로서 배치 운영 및 장애와 관련된 대처가 가능하다.
- **DB와 연동할 경우 필수적으로 메타 테이블이 생성되어야 한다.**
- Mysql의 경우 Job, Step 관련 6개의 테이블과 3개의 시퀀스를 생성한다.

### **스키마 생성 설정**

데이터베이스 스키마는 수동 및 자동으로 생성할 수 있다. (운영 환경에서는 수동으로 생성하여 설정하는 것을 권장.)

- **수동 생성 방법**
    
    `schema-mysql.sql` 파일에 작성된 쿼리를 복사하여 직접 실행.
    
- **자동 생성 방법**
`spring.batch.jdbc.initialize-schema=always` : 스크립트를 항상 실행
    
    `spring.batch.jdbc.initialize-schema=embedded`: 내장 DB일 때만 실행되며 스키마가 자동 생성 (default)
    
    `spring.batch.jdbc.initialize-schema=naver`: 스크립트 실행 X
    

### **Metadata Schema**

Spring batch metadata schema 

| Table | 설명 |
| --- | --- |
| batch_job_instance | Job이 실행될 때 JobInstance 정보가 저장됨. 실행되는 Job의 name, key에 대한 데이터를 저장. 
(JobInstance : Job의 실행 Instance) |
| batch_job_execution | Job의 실행 정보가 저장되며 Job의 생성, 시작, 종료 시각, 실행 상태, 메시지 등을 관리. |
| batch_job_execution_params | Job과 함께 실행되는 JobParameters 정보를 저장.  
(JobParameters: Job을 실행하는 데 필요한 파라미터) |
| batch_job_execution_context | Job의 실행 동안 여러 상태 정보, 공유 데이터를 직렬화(JSON) 해서 저장. Step 간의 공유가 가능함. |
| batch_step_execution | Step의 실행 정보가 저장되며 Step의 생성, 시작, 종료 시각, 실행 상태, 메시지 등을 관리. |
| batch_step_execution_context | Step의 실행 동안 여러 상태 정보, 공유 데이터를 직렬화(JSON) 해서 저장. Step 별로 저장되며 Step 간 데이터를 공유할 수 없음. |
- batch_job_execution_context
    
    ```powershell
    {"batch.version":"5.1.1"}
    ```
    
- batch_step_execution_context
    
    ```powershell
    {"batch.tasklet.Type":"com.study.opensearch.config.LogRegisterJobConfig$Lambda$1248/000000008013f952","batch.version":"5.1.1","batch.step.Type":"org.springframework.batch.core.repository.support.TaskletStepBuilder@batcheswork.batcheswork.batch.config.TaskletTaskConfiguration$$Lambda$1248/000000008013f952"}
    {"batch.tasklet.Type":"jdk.proxy2.$Proxy118","batch.version":"5.1.1"}
    ```
    

각 테이블에 대한 컬럼에 대한 설명은 [공식 문서](https://docs.spring.io/spring-batch/reference/schema-appendix.html#metaDataSchema)를 참고.

### **Spring Batch Scope (@JobScope, @StepScope)**

Spring Batch Scope는 Job, Step의 Bean 생성 및 실행에 관여하는 Scope이다.

`@JobScope` 와 `@StepScope`는 스프링의 기본 Scope인 Singleton 방식과는 대치되는 역할을 한다. Bean의 생성 시점을 Spring Application이 실행되는 시점이 아닌 `@JobScope` 와 `@StepScope` 가 명시된 메서드가 실행될 때까지 지연 시키는 것을 의미한다. (**Bean의 실행 시점에서 이루어 진다.**)이러한 행위를 ***Late Binding*** 이라고 한다.

### ***Late Binding(lazy binding) ?***

- **JobParameter를 특정 메서드가 실행하는 시점까지 지연 시켜 할당시킬 수 있다.** 
즉, 애플리케이션이 구동 되는 시점이 아니라 비즈니스 로직이 구현되는 어디는 JobParameter를 할당함으로 유연한 설계를 가능하게 한다.
- **병렬처리에 안전하다.** 
Step의 구성요소(ItemReader, ItemProcessor, ItemWriter)에서 데이터를 읽어 오는 메서드를 서로 다른 Step으로 부터 동시에 병렬 실행이 된다면 서로 상태를 간섭받게 될 수 있다. 하지만 Late Binding을 하면 각각의 Step에서 실행될 때 서로의 상태를 침범하지 않고 처리를 완료할 수 있다.

### @JobScope

- Step 선언문에 정의.
- `@Value` : jobParameter, jobExecutionContext 사용 가능.

### @StepScope

- Tasklet이나 ItemReader, ItemProcessor, ItemWriter 선언문에 정의.
- `@Value` : jobParameter, stepExecutionContext 사용 가능.

### Tasklet Interface

Tasklet은 간단한 작업 단위를 나타내며, 일반적으로 하나의 트랜잭션 내에서 수행되는 작업이다.

- Tasklet 인터페이스
    
    ```java
    package org.springframework.batch.core.step.tasklet;
    
    import org.springframework.batch.core.StepContribution;
    import org.springframework.batch.core.scope.context.ChunkContext;
    import org.springframework.batch.repeat.RepeatStatus;
    import org.springframework.lang.Nullable;
    
    @FunctionalInterface
    public interface Tasklet {
        @Nullable
        RepeatStatus execute(StepContribution contribution, ChunkContext chunkContext) throws Exception;
    }
    ```
    
    하나의 추상 메서드 `execute`를 가지고 있다. 이 메서드는 람다 표현식이나 메서드 참조로 구현할 수 있다. 유일한 추상 메서드이며, 이 메서드를 구현하여 실제 작업 로직을 작성한다.
    
    **StepContribution**
    
    현재 Step의 실행 중에 기여하는 정보를 나타낸다.
    
    - 읽기, 쓰기, 필터링 된 항목의 개수를 업데이트
    - Step 실행의 컨텍스트를 수정하거나 업데이트
    - 현재 Step의 종료 상태를 설정
    
    ```java
    contribution.incrementReadCount();
    contribution.incrementWriteCount(10);
    contribution.setExitStatus(ExitStatus.COMPLETED);
    ```
    
    **ChunkContext** 
    
    chunk 지향 처리의 실행 컨텍스트를 제공한다.
    
    - Step 실행의 컨텍스트를 포함하며, chunk가 속한 Step에 대한 정보를 제공
    - chunk 실행 중에 필요한 추가 속성들을 저장
    
    ```java
    Map<String, Object> attributes = chunkContext.getAttributes();
    attributes.put("startTime", System.currentTimeMillis());
    ```
    

## 실습 - SpringBatch 기본 설정

SpringBatch 사용을 위한 기본적인 설정만 설명한다.

*(Java 17 & Spring Boot 3.2.5 사용)*

1. **의존성 추가**
    
    기본적으로 배치와 관련된 메타데이터를 저장하는 DB가 필요하다. 그렇기 때문에 SpringBatch 관련 의존성과 함께 **DB 관련 의존성도 각자 사용하고자 하는 DB에 맞게 추가해주어야 한다.**
    
    ```bash
    dependencies {
    	// spring batch
    	implementation 'org.springframework.boot:spring-boot-starter-batch'
    }
    ```
    
2. **SpringBatch 메타 데이터 스키마 추가**
    
    `schema-mysql.sql` 파일로 SpringBatch 에 사용되는 메타데이터 스키마 쿼리를 확인할 수 있다. 해당 sql을 실행하여 테이블들을 모두 생성한다.
        
    직접 추가하지 않고 설정 파일의 설정 값을 통해 스키마가 자동 생성되도록 할 수 있다.
    
    ```bash
    # SpringBatch, SpringScheduler
    #spring.batch.initialize-schema=always
    spring.batch.jdbc.initialize-schema=always
    spring.batch.job.enabled=false
    ```
    
    mysql 외 다른 쿼리는 아래 Github 링크를 참고하면 된다.
    
    [spring-batch/spring-batch-core/src/main/resources/org/springframework/batch/core at main · spring-projects/spring-batch](https://github.com/spring-projects/spring-batch/tree/main/spring-batch-core/src/main/resources/org/springframework/batch/core)
    
3. **SpringBatch 관련 어노테이션 추가**
    
    main 함수가 있는 클래스에 `@EnableBatchProcessing` 어노테이션을 붙여준다.
    
    *SpringBatch 5부터는 main 애플리케이션에 `@EnableBatchProcessing`  어노테이션을 사용할 필요가 없다.*
    
    ```java
    import org.springframework.batch.core.configuration.annotation.EnableBatchProcessing;
    import org.springframework.boot.SpringApplication;
    import org.springframework.boot.autoconfigure.SpringBootApplication;
    import org.springframework.scheduling.annotation.EnableScheduling;
    
    **@EnableScheduling
    @EnableBatchProcessing**
    @SpringBootApplication
    public class DemoApplication {
    
    	public static void main(String[] args) {
    		SpringApplication.run(DemoApplication.class, args);
    	}
    
    }
    ```
    
4. **Config class 파일 추가**
    
    SpringBatch 사용을 위한 Config 파일 추가.
    
    ```java
    import org.springframework.batch.core.configuration.annotation.EnableBatchProcessing;
    import org.springframework.context.annotation.Configuration;
    
    @Configuration
    @EnableBatchProcessing
    public class BatchConfig {
    }
    ```
    
    <aside>
    🚨 SpringBatch 5.0.0 이후에 달라지는 설정이 있기 때문에 주의하여 사용해야 한다.
    
    </aside>
    

## 실습 - Tasklet

SpringBatch에서 **Tasklet은 Task 처리를 여러 단계로 구분하지 않고 하나의 Task만 수행하기 위한 용도로 사용된다.** 

기본적으로 배치 처리를 수행할 때 데이터를 조회하고, 쓰는 작업이 진행된다. Tasklet은 이 모든 작업을 한 번의 트랜잭션 처리를 통해 수행된다. 그렇기 때문에 조회 및 쓰기가 모두 적용될 때까지 대기하게 된다. (**Tasklet 방식은 대용량 처리를 수행할 때는 적합하지 않다.)**

하지만 단계를 구분하지 않고 하나의 Task에 모든 작업을 정의하기 때문에 **간단한 처리를 수행할 때는 오히려 Tasklet을 사용하는 것이 더 효과적**이다. 

Tasklet은 단순한 작업을 수행하거나 배치 작업의 전후에 필요한 사전/사후 처리를 수행하는 데 유용하다. 아래는 Tasklet을 사용하면 좋은 상황의 예시이다.

- **데이터베이스 테이블 초기화**
대규모 배치 작업 전에 특정 테이블을 초기화해야 하는 경우 Tasklet을 사용하여 단일 트랜잭션 내에서 초기화 작업을 수행할 수 있다.
- **파일 삭제**
    
    배치 작업 전에 임시 파일이나 이전 실행의 로그 파일을 삭제해야 하는 경우 Tasklet을 사용하여 해당 작업을 수행할 수 있다.
    
- **설정 파일 읽기**
    
    배치 작업 전에 설정 파일을 읽어와서 설정 값을 설정해야 하는 경우 Tasklet을 사용하여 해당 작업을 수행할 수 있다.
    
- **로그 남기기**
    
    특정 시점에 로그를 남겨야 하는 경우 Tasklet을 사용하여 로그 작업을 수행할 수 있다.
    
- **API 호출**
    
    외부 API를 호출해야 하는 경우 Tasklet을 사용하여 해당 작업을 수행할 수 있다.
    

### 로그 남기기 예제

- *Tasklet으로 구현하는 이유*
    
    **1. 배치 작업의 모듈화와 재사용성**
    
    로그 남기기 작업을 Tasklet으로 분리하면, 이 Tasklet을 다른 배치 작업에서도 재사용할 수 있다. 각 작업을 독립적인 모듈로 분리하면 코드의 가독성과 유지보수성이 향상된다.
    
    **2. 배치 작업의 유연한 구성**
    
    로그 남기기 작업을 특정 단계의 시작이나 끝에 쉽게 삽입할 수 있으며, 필요에 따라 다른 Tasklet과 조합하여 배치 작업의 흐름을 동적으로 변경할 수 있다.
    
    **3. 일관된 트랜잭션 관리**
    
    스프링 배치는 각 Step을 트랜잭션 단위로 관리한다. Tasklet으로 로그 남기기 작업을 수행하면, 해당 작업도 트랜잭션 관리의 일환으로 처리된다. 이는 작업의 일관성과 원자성을 보장한다. 만약 색인 작업 전에 로그를 남기는 코드가 실패하면, 전체 Step이 롤백되고 재시작할 수 있다.
    
    **4. 단계별 실행 및 오류 처리**
    
    Tasklet을 사용하면 각 단계를 독립적으로 실행하고 오류를 처리할 수 있다. 예를 들어, 로그 남기기 작업이 실패했을 때, 이를 별도의 오류로 처리할 수 있으며, 전체 배치 작업에 영향을 미치지 않도록 할 수 있다. Tasklet은 이러한 세밀한 오류 처리와 예외 처리를 가능하게 한다.
    
    **5. 가독성과 유지보수성**
    
    Tasklet을 사용하여 각 작업을 명확하게 분리하면, 코드의 가독성과 유지보수성이 향상됩니다. 특정 작업이 어디서 수행되고 있는지 명확히 알 수 있으며, 필요에 따라 각 Tasklet의 동작을 개별적으로 테스트하고 디버깅할 수 있다.
    

<aside>
❓ **n일 이전에 작성된 로그 데이터 삭제 작업을 수행하는 Job 을 만들어 보자. 
이때 수행할 Job에 대한 내용을 DB에 저장해보자. 
(아래 정보 참고)

table:** application_log_entity

**JobConfiguration:** ManageLogJobConfig
**Job:** manageLogJob
**Step**: registerLogStep, deleteLogStep
**Tasklet**: registerLogTasklet, deleteLogTasklet

</aside>

application_log_entity table properties

- **소스 코드**
    - *LogRegisterJobConfig.java*
        
        ```java
        package com.study.opensearch.config;
        
        import com.study.opensearch.domain.ApplicationLogEntity;
        import com.study.opensearch.domain.ApplicationLogEntityRepository;
        import com.study.opensearch.util.Constants;
        import lombok.RequiredArgsConstructor;
        import lombok.extern.slf4j.Slf4j;
        import org.springframework.batch.core.Job;
        import org.springframework.batch.core.Step;
        import org.springframework.batch.core.configuration.annotation.StepScope;
        import org.springframework.batch.core.job.builder.JobBuilder;
        import org.springframework.batch.core.repository.JobRepository;
        import org.springframework.batch.core.step.builder.StepBuilder;
        import org.springframework.batch.core.step.tasklet.Tasklet;
        import org.springframework.batch.repeat.RepeatStatus;
        import org.springframework.beans.factory.annotation.Value;
        import org.springframework.context.annotation.Bean;
        import org.springframework.context.annotation.Configuration;
        import org.springframework.orm.jpa.JpaTransactionManager;
        
        import java.time.LocalDateTime;
        
        @Configuration
        @RequiredArgsConstructor
        @Slf4j
        public class ManageLogJobConfig {
            private final JobRepository jobRepository;
            private final JpaTransactionManager transactionManager;
            private final ApplicationLogEntityRepository applicationLogEntityRepository;
        
            @Bean
            public Job manageLogJob() {
                return new JobBuilder("manageLogJob", jobRepository)
                        .start(registerLogStep())       // Job 이 처음 시작될 때 실행되는 step
                        .next(deleteLogStep())          // 이전 step 이 끝나면 실핼되는 step
                        .build();
            }
        
            /**
             * Tasklet 을 활용한 Log register Step
             *
             * @return Log register Step
             */
            @Bean
            public Step registerLogStep() {
                return new StepBuilder("registerLogStep", jobRepository)
                        .tasklet(registerLogTasklet(null), transactionManager)
                        .build();
            }
        
            /**
             * Log register Tasklet
             *
             * @param message Log message
             * @return Log register Tasklet
             */
            @Bean
            @StepScope
            public Tasklet registerLogTasklet(@Value("#{jobParameters['message']}") String message) {
                return (contribution, chunkContext) -> {
                    ApplicationLogEntity log = ApplicationLogEntity.builder()
                            .timestamp(LocalDateTime.now())
                            .level(Constants.LOG_LEVEL_INFO)
                            .message(message)
                            .userId(Constants.LOG_USER_ADMIN).build();
                    applicationLogEntityRepository.save(log);
        
                    return RepeatStatus.FINISHED;
                };
            }
        
            /**
             * Tasklet 을 활용한 Log delete Step
             * @return Log delete Step
             */
            @Bean
            public Step deleteLogStep() {
                return new StepBuilder("deleteLogStep", jobRepository)
                        .tasklet(deleteLogTasklet(null), transactionManager)
                        .build();
            }
        
            /**
             * Log delete Tasklet
             * @param days 삭제일
             * @return Log delete Tasklet
             */
            @Bean
            @StepScope
            public Tasklet deleteLogTasklet(@Value("#{jobParameters['days']}") String days) {
                return (contribution, chunkContext) -> {
                    LocalDateTime dayBefore = LocalDateTime.now().minusDays(Long.parseLong(days));
        
                    log.info("::: Delete logs prior to {} :::", dayBefore);
        
                    applicationLogEntityRepository.deleteLogBefore(dayBefore);
        
                    return RepeatStatus.FINISHED;
                };
            }
        }
        
        ```
        
    - *BatchConfig.java*
        
        ```java
        package com.study.opensearch.config;
        
        import lombok.RequiredArgsConstructor;
        import org.springframework.batch.core.Job;
        import org.springframework.batch.core.JobParameters;
        import org.springframework.batch.core.JobParametersBuilder;
        import org.springframework.batch.core.launch.JobLauncher;
        import org.springframework.boot.CommandLineRunner;
        import org.springframework.context.annotation.Bean;
        import org.springframework.context.annotation.Configuration;
        
        @Configuration
        @RequiredArgsConstructor
        public class BatchConfig {
            private final JobLauncher jobLauncher;
            private final Job manageLogJob;
        
            @Bean
            public CommandLineRunner run() {
                return args -> {
                    JobParameters jobParameters = new JobParametersBuilder()
                            .addString("message", "Delete log data 1 day ago.4")
                            .addString("days", "1")
                            .toJobParameters();
                    jobLauncher.run(manageLogJob, jobParameters);
                };
            }
        }
        ```
        
- **실행 로그**
    
    메서드 실행 시점에서 아래 로그를 출력하여 호출 및 실행 시점을 확인함.
    
    ```java
    log.info("::: [{}] method Start :::",  Thread.currentThread().getStackTrace()[1].getMethodName());
    ```
    
    ```powershell
    **<< Job -> Step -> CommandLineRunner >>**
    2024-05-28T11:11:58.343+09:00  INFO 55004 --- [demo] [           main] c.s.o.config.ManageLogJobConfig          : ::: [manageLogJob] method Start :::
    2024-05-28T11:11:58.348+09:00  INFO 55004 --- [demo] [           main] c.s.o.config.ManageLogJobConfig          : ::: [registerLogStep] method Start :::
    2024-05-28T11:11:58.378+09:00  INFO 55004 --- [demo] [           main] c.s.o.config.ManageLogJobConfig          : ::: [deleteLogStep] method Start :::
    2024-05-28T11:11:59.446+09:00  INFO 55004 --- [demo] [           main] c.study.opensearch.config.BatchConfig    : ::: [run] method Start :::
    
    **<< Tomcat 실행 >>**
    2024-05-28T11:12:02.077+09:00  INFO 55004 --- [demo] [           main] o.s.b.w.embedded.tomcat.TomcatWebServer  : Tomcat started on port 8080 (http) with context path ''
    2024-05-28T11:12:02.099+09:00  INFO 55004 --- [demo] [           main] com.study.opensearch.DemoApplication     : Started DemoApplication in 13.672 seconds (process running for 14.429)
    
    **<< Job launch (SimpleJob이 다음 매개변수로 시작되었다...) >>**
    2024-05-28T11:12:02.316+09:00  INFO 55004 --- [demo] [           main] o.s.b.c.l.support.SimpleJobLauncher      : Job: [SimpleJob: [name=manageLogJob]] launched with the following parameters: [{'message':'{value=Delete log data 1 day ago.5, type=class java.lang.String, identifying=true}','days':'{value=1, type=class java.lang.String, identifying=true}'}]
    
    **<< Step 실행 >>**
    2024-05-28T11:12:02.409+09:00  INFO 55004 --- [demo] [           main] o.s.batch.core.job.SimpleStepHandler     : Executing step: [registerLogStep]
    2024-05-28T11:12:02.462+09:00  INFO 55004 --- [demo] [           main] c.s.o.config.ManageLogJobConfig          : ::: [registerLogTasklet] method Start :::
    Hibernate: insert into application_log_entity (context,level,message,timestamp,user_id,id) values (?,?,?,?,?,?)
    2024-05-28T11:12:02.536+09:00  INFO 55004 --- [demo] [           main] o.s.batch.core.step.AbstractStep         : Step: [registerLogStep] executed in 126ms
    
    **<< Step 실행 >>**
    2024-05-28T11:12:02.583+09:00  INFO 55004 --- [demo] [           main] o.s.batch.core.job.SimpleStepHandler     : Executing step: [deleteLogStep]
    2024-05-28T11:12:02.601+09:00  INFO 55004 --- [demo] [           main] c.s.o.config.ManageLogJobConfig          : ::: [deleteLogTasklet] method Start :::
    2024-05-28T11:12:02.603+09:00  INFO 55004 --- [demo] [           main] c.s.o.config.ManageLogJobConfig          : ::: Delete logs prior to 2024-05-27T11:12:02.603216300 :::
    Hibernate: delete from application_log_entity where timestamp<?
    2024-05-28T11:12:02.708+09:00  INFO 55004 --- [demo] [           main] o.s.batch.core.step.AbstractStep         : Step: [deleteLogStep] executed in 124ms
    
    **<< Job complete (SimpleJob이 다음 매개 변수로 완료되었다...) >>**
    2024-05-28T11:12:02.743+09:00  INFO 55004 --- [demo] [           main] o.s.b.c.l.support.SimpleJobLauncher      : Job: [SimpleJob: [name=manageLogJob]] completed with the following parameters: [{'message':'{value=Delete log data 1 day ago.5, type=class java.lang.String, identifying=true}','days':'{value=1, type=class java.lang.String, identifying=true}'}] and the following status: [COMPLETED] in 377ms
    
    **<< CommandLineRunner 종료 >>**
    2024-05-28T11:12:02.743+09:00  INFO 55004 --- [demo] [           main] c.study.opensearch.config.BatchConfig    : ::: [lambda$run$0] method End :::
    ```
    

---

## 실습 - Chunk (2차)

[메모](https://www.notion.so/9242b14b409f44858240cb61700af32c?pvs=21)

SpringBatch에서 **Task 처리를 Chunk 단위를 이용하여 여러 개로 묶어 병렬적으로 처리**될 수 있도록 도와준다. Chunk란 데이터 덩어리로, **작업할 때 각 커밋 사이에 처리되는 row 수**를 의미한다. 즉, Chunk 지향 처리란 **한 번에 하나씩 데이터를 읽어 Chunk 라는 덩어리를 만든 뒤, Chunk 단위로 트랜잭션을 다루는 것을 의미**한다.

Chunk 단위로 트랜잭션을 수행하기 때문에 **실패할 경우에는 해당 Chunk 만큼만 롤백**이 되고, 이전에 커밋된 트랜잭션 범위까지는 반영이 된다.

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/8969bebe-5c25-4877-b1bd-7157fa55e4e0/Untitled.png)

- ItemReader에서 데이터를 하나 읽어온다.
- 읽어온 데이터를 ItemProcesser에서 가공한다.
- 가공된 데이터들을 별도의 공간에 모은 뒤, Chunk 단위만큼 쌓이게 되면 ItemWriter에 전달하고 ItemWriter는 일괄 저장한다.

***⇒ Reader와 Processer에서는 1건씩 처리되고, Writer에서는 Chunk 단위로 처리된다.***

### Mongo 데이터 Json 파일로 변환하기 예제

<aside>
📌 **MongoDB에서 색인 대상 데이터를 읽어와서 json 파일로 변환해보자.**

- ItemReader → MongoDB에서 색인 대상 데이터를 조회
- ~~ItemProcessor → 조회된 데이터를 처리~~
- ItemWriter → 처리된 데이터를 Json 파일로 저장
</aside>

- **소스 코드**
    - Job 생성 (MongoToJsonConfig.java)
        
        ```java
        import com.study.opensearch.entity.CommunityContents;
        import com.study.opensearch.util.Constants;
        import lombok.extern.slf4j.Slf4j;
        import org.springframework.batch.core.Job;
        import org.springframework.batch.core.Step;
        import org.springframework.batch.core.configuration.annotation.StepScope;
        import org.springframework.batch.core.job.builder.JobBuilder;
        import org.springframework.batch.core.repository.JobRepository;
        import org.springframework.batch.core.step.builder.StepBuilder;
        import org.springframework.batch.item.ItemProcessor;
        import org.springframework.batch.item.data.MongoCursorItemReader;
        import org.springframework.batch.item.data.builder.MongoCursorItemReaderBuilder;
        import org.springframework.batch.item.json.JacksonJsonObjectMarshaller;
        import org.springframework.batch.item.json.JsonFileItemWriter;
        import org.springframework.batch.item.json.builder.JsonFileItemWriterBuilder;
        import org.springframework.beans.factory.annotation.Qualifier;
        import org.springframework.beans.factory.annotation.Value;
        import org.springframework.context.annotation.Bean;
        import org.springframework.context.annotation.Configuration;
        import org.springframework.core.io.FileSystemResource;
        import org.springframework.data.domain.Sort;
        import org.springframework.data.mongodb.core.MongoTemplate;
        import org.springframework.data.mongodb.core.query.Criteria;
        import org.springframework.data.mongodb.core.query.Query;
        import org.springframework.transaction.PlatformTransactionManager;
        
        import java.util.Collections;
        
        @Slf4j
        @Configuration
        public class MongoToJsonJobConfig {
        
            private final JobRepository jobRepository;
        
            private final PlatformTransactionManager transactionManager;
        
            private final MongoTemplate mongoTemplate;
        
            private final Step registerLogStep;
        
            @Value("${index.docs.path}")
            private String indexDocsPath;
        
            @Value("${index.docs.name}")
            private String indexDocsName;
        
            @Value("${index.docs.keyCode}")
            private String indexDocsKeyCode;
        
            public MongoToJsonJobConfig(JobRepository jobRepository, PlatformTransactionManager transactionManager,
                                        MongoTemplate mongoTemplate,
                                        @Qualifier("registerLogStep") Step registerLogStep) {
                this.jobRepository = jobRepository;
                this.transactionManager = transactionManager;
                this.mongoTemplate = mongoTemplate;
                this.registerLogStep = registerLogStep;
            }
        
            @Bean
            public Job mongoToJsonJob() {
                return new JobBuilder("mongoToJsonJob", jobRepository)
                        .start(mongoToJsonStep())
                        .next(registerLogStep)
                        .build();
            }
        
            @Bean
            public Step mongoToJsonStep() {
                return new StepBuilder("mongoToJsonStep", jobRepository)
                        .<CommunityContents, CommunityContents>chunk(1000, transactionManager)
                        .reader(indexDocsItemReader())
                        .writer(jsonFileItemWriter(null))
                        .build();
            }
        
            @Bean
            public MongoCursorItemReader<CommunityContents> indexDocsItemReader() {
                return new MongoCursorItemReaderBuilder<CommunityContents>()
                        .name("indexDocsItemReader")
                        .template(mongoTemplate)
                        .targetType(CommunityContents.class)
                        .query(new Query().addCriteria(Criteria.where(Constants.DOC_KEY_CODE).is(indexDocsKeyCode)))
                        .sorts(Collections.singletonMap("publish_date", Sort.Direction.ASC))
                        .build();
            }
        
            @Bean
            @StepScope
            public JsonFileItemWriter<CommunityContents> jsonFileItemWriter(@Value("#{jobParameters['currentDate']}") String currentDate) {
                String filePath = indexDocsPath + indexDocsName + "_" + currentDate + ".json";
        
                return new JsonFileItemWriterBuilder<CommunityContents>()
                        .jsonObjectMarshaller(new JacksonJsonObjectMarshaller<>())
                        .resource(new FileSystemResource(filePath))
                        .name("jsonFileItemWriter")
                        .build();
            }
        }
        ```
        
    - Job 실행 (BatchRunnerConfig.java)
        
        ```java
        @Scheduled(cron = "${schedule.mongoToJsonJob.cron}")
            public void run() {
                log.info("::: [{}] method Start :::", Thread.currentThread().getStackTrace()[1].getMethodName());
        
                if(!useSchedule) {
                    return;
                }
        
                LocalDateTime date = LocalDateTime.now();
                String message = "Execute mongoToJsonJob at " + date.format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm"));
                String currentDate = date.format(DateTimeFormatter.ofPattern("yyyyMMddHHmmss"));
        
                try{
                    JobParameters jobParameters = new JobParametersBuilder()
                            .addString("keyCode", "BLIND")
                            .addString("currentDate", currentDate)
                            .addString("message", message)
                            .toJobParameters();
        
                    jobLauncher.run(mongoToJsonJob, jobParameters);
                }catch (Exception e){
                    log.error("mongoToJsonJob Error : {}", e.getMessage());
                }
            }
        ```
        

## 실습 - Chunk Rollback (2차)

파일 명: `MongoToJsonJobConfig.java`

processor 작업 처리 도중 예외가 발생하였다고 가정.

```java
private int count = 0;

...

    @Bean
    public Step mongoToJsonStep() {
        return new StepBuilder("mongoToJsonStep", jobRepository)
                .<CommunityContents, CommunityContents>chunk(1000, transactionManager)
                .reader(indexDocsItemReader())
                **.processor(indexDocsItemProcesser())**
                .writer(jsonFileItemWriter(null))
                .build();
    }
    
...

    @Bean
    public ItemProcessor<CommunityContents, CommunityContents> indexDocsItemProcesser() {
        return item -> {
            if(count == 1010){
                **throw new RuntimeException("강제 예외 발생...!!!!");**
            }
            count++;
          return item;
        };
    }
```

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/b13baecc-e052-4a90-8dc4-b357788f2e52/Untitled.png)

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/92b6beed-94d0-45c4-b915-0cccab09d1f1/Untitled.png)

Chunk 단위가 1000이기 때문에 이미 커밋된 트랜잭션 범위인 1번째~1000번째 데이터는 json 파일로 변환되었고, 실패한 Chunk인 1001번째 ~ 1010번째 데이터는 롤백되어 변환되지 않았다.

## FlowJob (2차)

Step을 순차적으로만 구성하는 것이 아닌 **특정한 상태에 따라 흐름을 전환하도록 구성**할 수 있다. `FlowJobBuilder`에 의해 생성된다.

- Step이 실패하더라도 Job은 실패로 끝나지 않도록 해야 하는 경우.
- Step이 성공했을 때 다음에 실행해야 할 Step을 구분해서 실행해야 하는 경우.
- 특정 Step은 전혀 실행되지 않게 구성해야 하는 경우.

Flow와 Job의 흐름을 구성하는 데만 관여하고 실제 비즈니스 로직은 Step에서만 이루어진다. FlowJob은 내부적으로 SimpleFlow 객체를 포함하고 있으며 Job 실행 시 호출된다. 단순한 Step으로 생성하는 SimpleJob 보다 FlowJob의 생성 구조가 더 복잡하고 많은 API를 제공한다.

### SimpleJob vs FlowJob

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/19d6eac7-d0ea-426e-9ae3-0d5a60b42954/Untitled.png)

- **소스 코드**
    
    ```java
    @Bean
    public Job batchJob() {
        return jobBuilderFactory.get("batchJob")
    				    // step1이 성공한다면 step3 실행
    				    // step1이 실패한다면 step2 실행
                .start(step1())
                .on("COMPLETED").to(step3())
                .from(step1())
                .on("FAILED").to(step2())
                .end()
                .build();
    }
    ```
    
    ```java
    import lombok.RequiredArgsConstructor;
    import lombok.extern.slf4j.Slf4j;
    import org.springframework.batch.core.ExitStatus;
    import org.springframework.batch.core.Job;
    import org.springframework.batch.core.Step;
    import org.springframework.batch.core.job.builder.JobBuilder;
    import org.springframework.batch.core.repository.JobRepository;
    import org.springframework.batch.core.step.builder.StepBuilder;
    import org.springframework.batch.core.step.tasklet.Tasklet;
    import org.springframework.batch.repeat.RepeatStatus;
    import org.springframework.context.annotation.Bean;
    import org.springframework.context.annotation.Configuration;
    import org.springframework.orm.jpa.JpaTransactionManager;
    
    @Slf4j
    @Configuration
    @RequiredArgsConstructor
    public class FlowJobConfig {
    
        private final JobRepository jobRepository;
    
        private final JpaTransactionManager transactionManager;
    
        @Bean
        public Job flowJob() {
            return new JobBuilder("flowJob", jobRepository)
                    // step1이 성공한다면 step3 실행
                    // step1이 실패한다면 step2 실행
                    .start(step1())
                    .on("COMPLETED").to(step3())
                    .from(step1())
                    .on("FAILED").to(step2())
                    .end()
                    .build();
        }
    
        @Bean
        public Step step1() {
            return new StepBuilder("step1", jobRepository)
                    .tasklet(tasklet1(), transactionManager)
                    .build();
        }
    
        @Bean
        public Tasklet tasklet1() {
            return (contribution, chunkContext) -> {
                // tasklet1 로직...
                log.info("::: Call tasklet1 :::");
    
    //            contribution.getStepExecution().setExitStatus(ExitStatus.FAILED);     // 강제 실패 처리
    
                return RepeatStatus.FINISHED;
            };
        }
    
        @Bean
        public Step step2() {
            return new StepBuilder("step2", jobRepository)
                    .tasklet(tasklet2(), transactionManager)
                    .build();
        }
    
        @Bean
        public Tasklet tasklet2() {
            return (contribution, chunkContext) -> {
                // tasklet2 로직...
                log.info("::: Call tasklet2 :::");
                return RepeatStatus.FINISHED;
            };
        }
    
        @Bean
        public Step step3() {
            return new StepBuilder("step3", jobRepository)
                    .tasklet(tasklet3(), transactionManager)
                    .build();
        }
    
        @Bean
        public Tasklet tasklet3() {
            return (contribution, chunkContext) -> {
                // tasklet3 로직...
                log.info("::: Call tasklet3 :::");
                return RepeatStatus.FINISHED;
            };
        }
    
    }
    
    ```


## 출처

[Spring Batch](https://spring.io/projects/spring-batch)

[[한 줄 용어]배치(Batch)란? (velog.io)](https://velog.io/@jch9537/%ED%95%9C-%EC%A4%84-%EC%9A%A9%EC%96%B4%EB%B0%B0%EC%B9%98Batch%EB%9E%80)

[[SpringBoot] SpringBatch 사용하기 (1) - Scheduler를 이용하여 Tasklet, Chunk 배치 만들기 (tistory.com)](https://jforj.tistory.com/353)

[[스프링] batch + scheduler로 주기적인 파일 삭제 구현 (tistory.com)](https://gimmesome.tistory.com/204)

[스프링 배치(Spring Batch) 시작하기 !😭 (tistory.com)](https://djlife.tistory.com/31)

[Spring Batch (3) DB 스키마 (tistory.com)](https://zzang9ha.tistory.com/426)

[@JobScope와 @StepScope (velog.io)](https://velog.io/@sa1341/JobScope%EC%99%80-StepScope)

[Spring Batch (10) @JobScope, @StepScope (tistory.com)](https://zzang9ha.tistory.com/434)

[Spring Batch - 개념, Tasklet Example(SimpleJob, FlowJob) (tistory.com)](https://fvor001.tistory.com/106)

https://velog.io/@ohzzi/Spring-Boot가-데이터베이스를-읽어오는-방법을-공식-문서를-통해-알아보자

[6. Spring Batch 가이드 - Chunk 지향 처리 (tistory.com)](https://jojoldu.tistory.com/331)

[Spring Batch - Reference Documentation](https://docs.spring.io/spring-batch/docs/4.0.x/reference/html/index-single.html#chunkOrientedProcessing)

[스프링 배치 실행 - Flow (tistory.com)](https://tonylim.tistory.com/432) (flow)

[[Spring Batch] 스프링 배치 실행 - Flow (tistory.com)](https://heekng.tistory.com/177)

openai chatgpt
