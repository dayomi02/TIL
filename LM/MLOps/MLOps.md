## MLOps

### MLOps 란

개발과 운영을 따로 나누지 않고 개발의 생산성과 운영의 안정성을 최적화 하기 위한 문화이자 방법론이 DevOps이며, 이를 ML 시스템에 적용한 것이 MLOps이다.

MLOps란 단순히 ML 모델 뿐만 아니라, 데이터를 수집하고 분석하는 단계, 그리고 ML 모델을 학습하고 배포하는 단계까지 전 과정을 AI Lifecycle로 보고, MLOps의 대상으로 보고 있다.

### ML 시스템의 요소

ML 시스템을 프로덱션 환경에 적용하고 운영하기 위해서는 단순히 좋은 ML 모델만으로 가능한 것이 아니다. ML 모델이 ML  시스템의 핵심이기는 하지만, 전체 프로덕션 ML 시스템의 운영을 고려하면 모델 학습 자체는 오히려 작은 부분을 차지한다고 얘기하기도 한다. 모델을 운영하기 윈해서는 기반 데이터와 인프라를 포함한 모든 시스템이 유기적으로 돌아가야 한다.
ML Code를 중심으로, Configuration, Automation, Data collection, Data verification, Feature engineering, Testing adn debugging Resource management, Model analysis, Provess nmanagement, Metadata mangement, Serving Infrastructure, Monitorting

### Data science steps for ML

먼저 business use case와 success criteria들을 정하고 나서 ML 모델을 프로덕션에 배포하기까지, 수동이든 자동이든 , 모든 ML 프로젝트에는 다음과 같은 스텝들이 수반된다.

1. Data Extraction (데이터 추출)
    
    데이터 소스에서 관련 데이터 추출
    
2. Data Analysis (데이터 분석)
    
    데이터의 이해를 위한 탐사적 데이터 분석(EDA) 수행. 모델에 필요한 데이터 스키마 및 특성 이해
    
3. Data Preparation (데이터 준비)
    
    데이터의 학습, 검증, 테스트 세트 분할
    
4. Model Training (모델 학습)
    
    다양한 알고리즘 구현, 하이퍼 파라미터 조정 적용. output은 학습된 모델.
    
5. Model Evaluation (모델 평가)
    
    holdout test set에서 모델을 평가. output은 모델의 성과 평가 metric.
    
6. Model Validation (모델 검증)
    
    기준치 이상의 모델 성능이 검증되고, 배포에 적합한 수준인지 검증.
    
7. Model Serving (모델 서빙)
    
    온라인 예측을 제공하기 위해 REST API가 포함된 마이크로 서비스. 배치 예측 시스템. 모바일 embedded 모델.
    
8. Model Monitoring (모델 모니터링)
    
    모델의 예측 성능을 모니터링
    

ML 프로세스의 자동화 수준에 따라 해당 ML 시스템의 성숙도를 평가해볼 수 있다. Google은 가장 보편적인 수동 적용 단계부터, ML과 Ci/CD pipline 을 모두 자동화하는 단계까지 성숙도를 세 단계의 레벨로 나누어서 제시함.

### MLOps level 0 : Manual process

- 데이터 추출과 분석 모델 학습, 검증을 포함한 단계가 수동임
- 

[[MLOps 정의] MLOps가 무엇인고?. MLOps의 정의, 그리고 ML Lifecycle에 대해 알아보자 | by Jaemun Jung | Medium](https://jaemunbro.medium.com/mlops%EA%B0%80-%EB%AC%B4%EC%97%87%EC%9D%B8%EA%B3%A0-84f68e4690be)

[MLOps의 구성요소와 오픈소스 (velog.io)](https://velog.io/@inthecode/MLOps%EC%9D%98-%EA%B5%AC%EC%84%B1%EC%9A%94%EC%86%8C%EC%99%80-%EC%98%A4%ED%94%88%EC%86%8C%EC%8A%A4)
