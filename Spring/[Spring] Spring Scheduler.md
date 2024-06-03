# [Spring] Spring Scheduler
## 스케쥴러(Scheduler)?

특정한 시간에 등록한 작업을 자동으로 실행시키는 것. (Spring Scheduler, Spring Quartz)

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/6cb06cf7-6403-4d02-8d22-a08276bd3ae7/Untitled.png)

- 수집 데이터를 Json 파일로 변환하는 작업. **→ Batch**
- 해당 작업은 매일 01시에 진행. **→ Scheduler**

## Spring Scheduler?

Spring Framework에서 기본적으로 제공하는 Scheduler.

### 특징

- Spring Framework의 기본 기능이기 때문에 추가적인 의존성이 불필요 함.
- `@Component` 와 `@Scheduler` 어노테이션으로 사용이 쉬움.
- 1개의 Thread pool을 사용하기 때문에 Schedule이 끝나야 다음 Schedule을 실행할 수 있음.

### Spring Scheduler 설정 옵션

`@Scheduled` 속성을 이용하여 스케쥴 옵션을 다양하게 설정할 수 있다. 속성에는 크게 fixedDelay, fixedRate, initDelay, cron 등이 있다.

1. **fixedDelay**
    
    scheduler가 **끝나는 시간 기준**으로 실행. 작업을 마친 후부터 주기 타이머가 돌아 메서드를 호출.
    
    - **`fixedDelay`** : milliseconds 단위. **이전 Task의 종료 시점**으로부터 1초 후 Task 실행.
        
        ```java
        @Scheduled(fixedDelay = 1000)
        public void run() {
        	log.info("fixedDelay Scheduler 실행");
        }
        ```
        
    - **`fixedDelayString`** : fixedDelay와 같은데 문자열로 값을 표현하겠다는 의미.
        
        ```java
        @Scheduled(fixedDelayString = "1000")
        public void run() {
        	log.info("fixedDelayString Scheduler 실행");
        }
        ```
        
2. **fixedRate**
    
    scheduler가 **시작하는 시간 기준**으로 실행. 작업 수행 시간과 상관없이 일정 주기마다 메서드를 호출.
    
    - `fixedRate` : milliseconds 단위로, **이전 Task의 시작 시점**으로부터 1초 후 Task 실행.
        
        ```java
        @Scheduled(fixedRate= 1000)
        public void run() {
        	log.info("fixedRate Scheduler 실행");
        }
        ```
        
    - `fixedRateString` : fixedRate와 같은데 문자열 값을 표현하겠다는 의미.
        
        ```java
        @Scheduled(fixedRateString  = "1000")
        public void run() {
        	log.info("fixedRateString  Scheduler 실행");
        }
        ```
        
3. **initialDelay**
    
    스케줄러에서 메서드가 등록되자마자 수행하는 것이 아닌 초기 지연 시간을 설정.
    
    - `initialDelay` : 스케줄러에서 메서드가 등록되자마자 수행하는 것이 아니라 초기 지연시간 3초 후에 5초마다 Task 실행.
        
        ```java
        @Scheduled(fixedRate= 5000, initialDelay = 3000)
        public void run() {
        	log.info("initialDelay Scheduler 실행");
        }
        ```
        
    - `initialDelayString` : initialDelay와 같은데 문자열로 값을 표현하겠다는 의미
        
        ```java
        @Scheduled(fixedRate= 5000, initialDelayString = "3000")
        public void run() {
        	log.info("initialDelayString Scheduler 실행");
        }
        ```
        
4. **cron**
    
    Cron 표현식을 사용하여 작업을 예약. 초, 분, 시 일, 월, 요일 (연도) 순으로 실행.
    
    Cron 표현식은 Scheduling의 정규 표현식을 의미한다. cron 설정은 리눅스의 crontab 기능과 유사하게 설정할 수 있다.
    
    Cron의 구성은 아래와 같이 총 6개의 필드로 구성된다.
    
    ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/804809b7-0f16-49fd-b972-3672af13f549/Untitled.png)
    
    cron 표현식에 대한 자세한 설명은 [참고 링크](https://zamezzz.tistory.com/197#google_vignette) 확인. 추가로 cron 표현식을 [생성해 주는 사이트](https://silverbullet.tistory.com/entry/Cron-%ED%91%9C%ED%98%84%EC%8B%9D-%EC%83%9D%EC%84%B1%ED%95%B4-%EC%A3%BC%EB%8A%94-%EC%82%AC%EC%9D%B4%ED%8A%B8)도 존재한다. 
    

[[Spring] Scheduler 어떤걸 사용해야 할까 ? - Spring Scheduler와 Spring Quartz](https://sabarada.tistory.com/113)

## 실습 - Spring Scheduler 기본 설정

1. 의존성 확인
    
    spring-boot-starter에 기본적으로 의존. org.springframework.scheduling
    
2. Spring Scheduler 사용을 위한 어노테이션 추가
    
    main 어플리케이션에 `@EnableScheduling` 어노테이션 추가.
    
    ```java
    import org.springframework.boot.SpringApplication;
    import org.springframework.boot.autoconfigure.SpringBootApplication;
    import org.springframework.scheduling.annotation.EnableScheduling;
    
    @EnableScheduling
    @SpringBootApplication
    public class DemoApplication {
    
        public static void main(String[] args) {
            SpringApplication.run(DemoApplication.class, args);
        }
    }
    ```
    
    scheduler를 사용할 클래스에 `@Component` , 메서드에 `@Scheduled` 추가.
    
    ```java
    package com.study.opensearch.config;
    
    import lombok.RequiredArgsConstructor;
    import lombok.extern.slf4j.Slf4j;
    import org.springframework.scheduling.annotation.Scheduled;
    import org.springframework.stereotype.Component;
    
    @Slf4j
    **@Component**
    @RequiredArgsConstructor
    public class ScheduleConfig {
    		
        **@Scheduled(fixedDelay = 50000)**
        public void run(){
            log.info("fixedDelay 실행");
        }
    }
    ```
    

### @Scheduled 규칙

- 메서드 반환 타입은 void.
- 메서드 매개변수 사용 불가능.

## 실습 - mongoToJsonJob Batch

- mongoToJsonJob 을 끝나는 시간을 기준으로 5분 후에 실행하도록 Spring Scheduler 설정.
    
    ```java
    @Scheduled(fixedDelay = 300000)
        public void run() {
            log.info("::: [{}] method Start :::", Thread.currentThread().getStackTrace()[1].getMethodName());
    
            String message = "Execute mongoToJsonJob at " + LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyyMMddHHmm"));
            try{
                JobParameters jobParameters = new JobParametersBuilder()
                        .addString("keyCode", "BLIND")
                        .addString("message", message)
                        .toJobParameters();
                jobLauncher.run(mongoToJsonJob, jobParameters);
            }catch (Exception e){
                log.error("mongoToJsonJob Error : {}", e.getMessage());
            }
        }
    ```
    
    ```java
    public class MongoToJsonJobConfig {
    ...
    @Bean
        public Job mongoToJsonJob() {
            return new JobBuilder("mongoToJsonJob", jobRepository)
                    .start(mongoToJsonStep())    // mongo 데이터 json 파일로 변환 작업 수행
                    .next(registerLogStep)       // db에 log 저장 작업 수행
                    .build();
        }
    ...
    ```
    
- 실행 결과 확인
    
    ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/c719c4c9-0ee3-4298-8f32-15a1bac75b39/Untitled.png)
    
    ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/23052f5e-0299-4ea2-8ee8-13bff580cc80/Untitled.png)
    
    ![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/166b42a2-f4e8-4fa2-9cc8-b929e7440ae6/Untitled.png)
    

## 실습 - Scheduler 설정 분리

애플리케이션을 개발하다 보면 하드 코딩 보다는 유연할 설정(환경 설정 파일에서 관리)을 지원하는 것이 필요하다.

- application.yml 파일에 Scheduler 설정
    
    ```yaml
    # scheduler
    schedule:
      mongoToJsonJob:
        cron: 0 0/2 * * * *
        use: true
    ```
    
- 환경 설정 값 사용하도록 소스코드 수정
    
    ```java
    **@Value("${schedule.mongoToJsonJob.use}")**
        private boolean useSchedule;
    
    ...
    
    **@Scheduled(cron = "${schedule.mongoToJsonJob.cron}")**
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
    

## 출처

[[Spring] Batch와 Scheduler의 차이 [Spring Scheduler 사용방법] — 예르미의 코딩노트 (tistory.com)](https://yermi.tistory.com/entry/Spring-Batch%EC%99%80-Scheduler%EC%9D%98-%EC%B0%A8%EC%9D%B4-Spring-Scheduler-%EC%82%AC%EC%9A%A9%EB%B0%A9%EB%B2%95)

[[Spring Boot] @Scheduled를 이용한 스케쥴러 구현하기 (velog.io)](https://velog.io/@developer_khj/Spring-Boot-Scheduler-Scheduled)

[[Spring Boot] Scheduler 사용해보기(일정 주기로 실행하는 스프링 스케쥴러) (tistory.com)](https://data-make.tistory.com/699)
