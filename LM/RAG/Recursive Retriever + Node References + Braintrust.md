# **Recursive Retriever + Node References + Braintrust 문서 정리**

이 가이드에서는 recursive retrieval을 사용하여 노드 관계를 탐색하고 "references"(참조)를 기반으로 노드를 가져오는 방법을 보여줍니다.

Node references는 강력한 개념이다. 처음 검색을 수행할 때 원시 텍스트가 아닌 참조를 검색하기를 원할 수 있다. 여러 참조가 동일한 노드를 가리키도록 할 수 있다.

이 가이드에서는 노드 참조의 몇 가지 다른 용도를 살펴봅니다:

- **Chunk references(**청크 참조) : 더 큰 청크를 지칭하는 청크 크기가 다름
- **Metadata references(**메타데이터 참조) : 요약 + 더 큰 청크를 참조하는 생성된 질문

[Braintrust](https://www.braintrustdata.com/)(브레인트러스트)는 재귀 검색 + 노드 참조 방법이 얼마나 잘 작동하는지 평가한다. 브레인트러스트는 인공지능 제품을 구축하기 위한 엔터프라이즈급 스택이다. 평가부터 신속한 놀이터, 데이터 관리에 이르기까지 불확실성과 테디움을 활용해 인공지능을 비즈니스에 접목한다.

## **Baseline Retriever**

유사성을 내장하여 상위 k개의 원시 텍스트 노드를 단순히 가져오는 baseline retriever를 정의한다.

```python
base_index = VectorStoreIndex(base_nodes, embed_model=embed_model)
base_retriever = base_index.as_retriever(similarity_top_k=2)

retrievals = base_retriever.retrieve(
    "Can you tell me about the key concepts for safety finetuning"
)

for n in retrievals:
    display_source_node(n, source_length=1500)

query_engine_base = RetrieverQueryEngine.from_args(base_retriever, llm=llm)

response = query_engine_base.query(
    "Can you tell me about the key concepts for safety finetuning"
)
print(str(response))
```

### Chunk References: Smaller Child Chunks Referring to Bigger Parent Chunk (newParent2)

더 큰 부모 청크를 참조하는 더 작은 자식 청크

이 사용 예에서는 더 큰 부모 청크를 가리키는 더 작은 청크의 그래프를 구축하는 방법을 보여준다.

쿼리 시간 동안 우리는 더 작은 청크를 검색하지만 더 큰 청크에 대한 참조를 따른다. 이를 통해 합성을 위한 더 많은 컨텍스트를 가질 수 있다.

**base 노드와 어떻게 만들어지는 지 관계를 확인해보자**

[note](https://www.notion.so/note-b79f39fe8ebe4ac48f89113c817633c2?pvs=21)

- 검색 결과를 보면 base_node가 출력된다. 
내부적으로 query  검색을 할 때 작은 청크에서 검색 하고, 참조 문서로는 더 큰 청크를 사용하는 것 같음…
- 원본 문서 전체가 있어야 함.

### **Metadata References: Summaries + Generated Questions referring to a bigger chunk (newParent3)**

요약 + 더 큰 청크를 참조하는 생성된 질문

이 사용 예에서는 소스 노드를 참조하는 추가 컨텍스트를 정의하는 방법을 보여줍니다.

이 추가 컨텍스트에는 생성된 질문뿐만 아니라 요약도 포함됩니다.

쿼리 시간 동안 우리는 더 작은 청크를 검색하지만 더 큰 청크에 대한 참조를 따른다. 이를 통해 합성을 위한 더 많은 컨텍스트를 가질 수 있다.

- json line 파일 데이터 읽어서 처음에 문서에서 가져와서 생성해뒀던 base_nodes에다가 정보 추가.  → all_nodes
- 나머지는 위와 동일

[Recursive Retriever + Node References + Braintrust - LlamaIndex](https://docs.llamaindex.ai/en/stable/examples/retrievers/recurisve_retriever_nodes_braintrust/)
