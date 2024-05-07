## Hibernate **Validator Annotation**

필드에 붙여 사용하는 hibernate validator annotarion

| Annotation | 용도 |
| --- | --- |
| @NotBlank | CharSequence  타입 필드에 사용되어 문자열이 null이 아니고, 앞뒤 공백 문자를 제거한 후 문자열 길이가 0보다 크다는 것을 검사한다. |
| @NotEmpty | CharSequence, Collectio, Map 타입과 배열에 사용되어 null이 아니고 비어있지 않음을 검사한다. |
| @NotNull | 모든 타입에 사용할 수 있으며 null이 아님을 검사한다. |
| @Min(value=) | 최솟값을 지정해서 이 값보다 크거나 같은지 검사한다. |
| @Max(value=) | 최댓값을 지정해서 이 값보다 작거나 같은지 검사한다. |
| @Pattern(regex=, max=) | regex로 지정한 정규표현식을 준수하는 지 검사한다. 정규표현식의 플래그(flag)도 사용할 수 있다.
flag: 정규 표현식 플래그를 통해 대소문자 구분, 멀티 라인 허용, 유니코드 허용 등을 지정할 수 있다. |
| @Size(min=, max=) | 개수의 최솟값, 최댓값을 준수하는지 검사한다. |
| @Email | 문자열이 유효한 이메일 주소를 나타내는지 검사한다. |


출처: 실전 스프링 부트 - 기본 개념부터 실무 베스트 프랙티스, 그리고 GraalVM, GraphQL, R소켓 등 최신 기술까지 
