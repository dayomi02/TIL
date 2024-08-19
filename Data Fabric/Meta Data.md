중요한 이유

- 검색성
- 범용성

메타 데이터 작성 = 마인드 맵

## 질문

### 의견

- 어느정도 메타 데이터가 만들어 지면, 만들어진 메타 데이터를 가지고 LLM을 사용하여 새로운 메타 정보를 뽑을 수 있지 않을까?
이렇게 만들어진 메타 데이터는 꼭 사용하지 않더라고 선택 값으로 사용할 지 사용하지 않을 지 선택 가능하도록 구현하면 어떨지… 나중에 그래프 연동까지 되었을 때 그래프가 얼마나 더 풍성해질 수 있는지 볼 수 있을 거 같음…

### 질문

- 우리만의 표준 메타를 만들었다고 하면, 표준 메타 형식에 맞게 실제 content는 어떻게 작성되어야 하는 게 맞는가?  자동으로 작성해주는 모델을 개발해야 하는 건가? 사용자한테 먼저 입력을 받고 그 내용을 바탕으로 모델을 돌려 더 많은 메타를 뽑아야 하는 건가? 그렇게 해서 만들어진 메타는 다시 사용자가 수정할 수 있어야 하는 건가?
    
    ⇒ 100% 자동.
    

## Google Data Catalog

<aside>
📌 구글 Data Catalog는 싱커, 메타데이터 저장소, 검색 색인 이렇게 크게 세 구조로 되어있다.
우리도 동일하게 구조를 가도 되지 않을까.. (검색 색인 제외(아님). 싱커(?)에서 분석 후 메타 정의, 정의한 메타를 저장소에 저장. 메타 데이터 저장소 데이터를 그래프 형식으로 변환…)

Google Dataplex에서의 Data Catalog(표준 메타)는 **기술 메타데이터**와 **비즈니스 메타데이터**라는 두 가지 유형의 메타데이터를 처리한다. 

새로운 개념을 도입하여 메타 데이터 간의 관계 정의를 더 자세하게 할 수 있다. (”**태그**” 개념 사용. 테이블에도 붙일 수 있고, 필드에도 붙일 수 있고..)

메타 관리 관련해서 **정책 관리**도 생각해보고, 관련 기능도 함께 구현이 되어야 할 거 같음.

</aside>

https://cloud.google.com/data-catalog/docs/concepts/overview?hl=ko

https://youtu.be/M9rN67vC1hA?si=SI3M3SlhJMMVxrgq

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/0017d648-6953-429d-8a65-ee5a14577bc0/Untitled.png)

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/d0fbe810-1c70-4c94-9a0d-770a5164d223/Untitled.png)

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/d226918c-4d30-464a-90c4-904e87b285f1/Untitled.png)

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/6f0c3e96-6f61-447b-93e2-a9abedb5c82b/Untitled.png)

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/178b599e-5d7e-43db-a094-891586ae1104/Untitled.png)

태그를 통해서 메타데이터 강화

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/8025fd2a-3db1-42c1-9268-b10062fe1ceb/Untitled.png)

권한 제어 필수인 듯

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/9fe68c05-e470-41d7-9830-8893b523aa5f/Untitled.png)

## 메타 데이터 표준

### 메타 데이터 설계 지침서

<aside>
📌 **대표적인 메타데이터 항목**을 기본적으로 사용해보는 건..?

</aside>

https://dataon.kisti.re.kr/data_mgnt_guideline_09.do

### **Azure Purview 에서의 메타 데이터 설명**

<aside>
📌 사용할 데이터가 확정되면 아래 내용을 먼저 확인해야 한 뒤 상세한 메타 데이터 구성을 하는 순서가 맞을 듯.
****

- 기술 메타데이터, 비즈니스 메타데이터,  운영 메타데이터, 소셜 메타데이터 등 우리가 사용할 메타 데이터는 무엇인지 정하기
- 중요한 비즈니스 메타데이터는 무엇인가?
- 상호 운용성에 필요한 기술 메타데이터는 무엇인가?
- 데이터를 캡처하는 프로세스와 스트림은 무엇인가?
- 모델 또는 스키마를 만들고 유지 관리하는 위치는 어디인가?
- 데이터 거버넌스 부서가 올바르게 작업을 수행할 수 있도록 중앙에서 제공해야 하는 정보는 무엇인가?
</aside>

![Untitled](https://prod-files-secure.s3.us-west-2.amazonaws.com/46f64df6-9c9c-4b4d-990a-52c9828dc042/cb16736b-7845-4166-922c-9f3848a935c6/Untitled.png)

https://learn.microsoft.com/ko-kr/azure/cloud-adoption-framework/scenarios/cloud-scale-analytics/govern-metadata-standards

## Delta Sharing

Delta Sharing은  대규모 데이터 세트의 안전한 실시간 교환을 위한 개방형 프로토콜로, 조직이 사용하는 컴퓨팅 플랫폼에 관계없이 실시간으로 데이터를 공유할 수 있습니다.
• Databricks: 오픈 소스 Delta Sharing과 통합형 데이터 카탈로그를 사용해 조직 내에서는 물론 여러 조직 간에 데이터를 중앙집중식으로 공유 및 관리

https://learn.microsoft.com/ko-kr/azure/databricks/data-sharing/

https://www.databricks.com/product/delta-sharing

데이터를 보고 메타로 쓸만한 걸 찾기

**+ 다른 분야의 데이터를 어떻게 메타로 연결할 수 있는지 고민하는 게 중요함!!!**

데이터가 정리가 되면 메타 데이터 구성 → 수집
