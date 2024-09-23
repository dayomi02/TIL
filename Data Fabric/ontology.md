## 용어

**Semantic Web : 시맨틱 웹**

- 웹 상의 데이터를 기계가 이해할 수 있도록 온톨로지 형태로 구조화하는 기술과 표준의 집합
- 웹 페이지의 내용이 사람 뿐만 아니라 컴퓨터에 의해서도 “이해”될 수 있도록 만드는 것을 목표

**RDF (Resource Description Framework) : 자원 설명 프레임워크**

- 웹 상의 정보를 모델링하고 구조화하기 위한 표준 프레임워크, 소프트웨어가 웹의 데이터를 더 잘 이해하고 지능적으로 처리하도록 함.
- 프리플 기반 데이터 모델. 데이터를 주어(Subject), 서술어(Predicate), 목적어(Object) 의 형태로 표현하여, 정보의 의미와 관계를 명확하게 정의
- 유연한 데이터 통합. RDF는 다양한 출처에서 온 데이터를 통합하고 연결하는 데 유용. RDF의 표준화된 모델 분석에 서로 다른 형식으나 스키마를 가진 정보도 쉽게 결합하고 확장 가능.

**OWL (Ontology Web Language) : 온톨로지 웹 언어**

- 웹 상의 데이터와 그 관계에 대한 복잡한 온톨로지를 정의하는데 사용되는 언어
- 데이터 간의 의미 있는 연결을 만들고, 컴퓨터가 데이터의 구조와 의미를 “이해”할 수 있도록 도움

**Ontology : 온톨로지**

- 개념 체계 및 관계, 데이터와 그 데이터 간의 관계, 데이터의 속성 등을 체계적으로 정리하여 표현하는 것
- 데이터 간의 복잡한 관계를 표현하고, 컴퓨터에게 해당 도메인의 지식을 “이해”할 수 있는 구조를 제공

**URI (Uniform Resource Identifier) : 통합 자원 식별자**

- 인터넷 상에 존재하는 각종 자원(웹페이지, 이미지, 동영상 등)을 나타내는 고유한 주소. 웹사이트 주소나 이메일 주소 등

**XML (EXtensible Markup Language) : 확장 가능 마크업 언어**

- 데이터의 구조와 의미를 설명하는 태그(Tag)를 사용하여 메타 정보(데이터에 대한 데이터)를 표현하는 언어
- 네임스페이스(NS)는 같은 이름을 가진 태그나 속성이 혼동되지 않도록 구분해주며, XML 스키마는 데이터의 구조와 타입을 정의하는 규칙임

## 지식그래프 & 백터 데이터베이스

LLM은 유창하고 일관된 테스트를 생성하지만 종종 부정확하거나 일관성 없는 정보를 생성하는 문제가 있으며 이를 환각(Hallucination)이라고 한다. 이러한 문제를 해결하기 위해 백터 데이터베이스나 지식 그래프와 같은 오부 지식 소스를 활용하는 방법이 제안되었다.

### 벡터 데이터베이스 (Vector Database)

- 고차원 백터의 모음으로, 단어, 구문, 문서와 같은 개체나 개념
    - “파리”와 “프랑스”가 “파리”와 “독일”보다 더 관련이 있다고 백터 거리를 통해 알 수 있음
- 데이터를 수치 배열로 저장
- 유사한 벡터를 검색하거나 특정 기준에 따라 벡터를 검색, 유사성 검색에 적합

### 지식 그래프 (Knowledge Graph)

- 개체나 개념과 그 관계를 나타내는 노드와 엣지의 모음
    - “파리”가 “프랑스”의 수도라는 사실을 엣지 라벨을 통해 알려줌
- 데이터를 노드와 엣지로 데이터를 저장
- 그래프 구조를 순회하고 특정 기준에 다라 노드, 관계, 패턴을 검색, 복잡한 관계와 의미 분석에 유용
- 지식 그래프의 주요 구성 요소
    - 정점/노드 : 지식 영역의 개체나 객체
    - 엣지 : 두 노드 사이의 관계
- 지식 그래프에서의 트리플
    - 주체(Subject), 목적(Object), 서술자(Predicate)로 구성
    - 지식 그래프 데이터의 기본 단위임
- 지식 그래프가 LLM 환각 문제에서 백터 데이터베이스보다 나은 이유
    - 지식 그래프는 벡터 데이터베이스보다 더 정확하고 구체적인 정보 제공
    - 다양하고 복잡한 쿼리를 지원하며, 더 많은 추론과 추론을 가능하게 함
    - LLM에게 더 정확하고 관련성 높은 텍스트를 생성하도록 함

## 온톨로지 설계

### 온톨로지

지식 정보 자원들 간의 의미 관계를 컴퓨터가 인식하여 지식 정보의 전달과 습득을 용이하게 하는 기술. 본래 철학적 개념으로, 존재를 탐구라는 학문에서 유래.

- 온톨로지 설계 요소
    - 설계를 위해서는 ‘클래스’, ‘속성(Attributes)’, ‘관계(Relationships)’의 세 가지 요소가 필요
- 온톨로지 구축 예시
    - 다양한 요소를 마인드맵 형태로 나열하고, 연관성에 다라 연결
    - 유사한 성격을 가진 요소들을 클래스로 범주화
    - 각 요소들의 고유한 정보를 속정으로 정의
    - 요소들 간의 의미 관계를 RDF 구문으로 설명하여 관계성을 부여

https://wisian.net/ontology/