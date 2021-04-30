# 에러 메시지
## 01. 컴파일 에러

컴파일 에러는 프로그램이 실행되기 전에 발견되는 에러로, 컴파일러가 이해하지 못하는 키워드나 문장부호, 구문의 쌍이 맞지 않는 등 문법적인 오류로 인해 컴파일 과정이 정상적으로 수행되지 않을 경우 발생한다.

예를 들어 ;(시미콜론)을 빠뜨리거나, 선언되지 않은 함수를 호출하거나, 함수의 return 값을 입력하지 않은 경우에 주로 발생한다.

<br>

## 02. 런타임 에러

런타임 에러는 프로그램 실행 중 발견되는 에러로, 문법적으로는 오류가 없으나 프로그램에서 수행할 수 없는 작업을 시도할 때 발생한다. 주로 설계 미숙으로 인한 경우가 많다.

런타임 에러가 발생하는 대표적인 경우는 숫자를 0으로 나눌 때, 반복문에서 빠져나올 수 없는 무한루프, 접근할 수 없는 주소에 접근을 시도하는 경우 등에 발생한다.

<br>

## 03. 에러의 종류

#### python

- NameError : name '...' is not defined
명령어 철자가 틀렸을 때 발생
- SysnaxError : Invalid syntax
구분이 잘못 쓰였을 때 발생 ( "",{},;)
- ImportError : No module named...
Import 명령으로 외부 모듈을 가져올 때 모듈의 이름이 잘못되었을 때
- Indentation Error : Expected an indented block
반복 블록의 들여쓰기가 올바르지 않을 때 발생
- ValueError : Invalid literal for ... ()
정수, 실수, 문자열 등 다른 자료형 사이에서 값을 변환할 때 변환이 불가능한 경우 발생 
ex ) a = int("abc")

#### java

- ClassNotFoundException
클래스를 찾지 못한 경우
- NoSuchMethodException
지정된 메소드가 없을 경우
- [IOException]FileNotFoundException
파일이 발견되지 않았을 때
- [IOException]InterruptedlOException
입출력 처리가 중단되었을 때
- [RuntimeException]ArithmeticException
제로제산 등의 산술 예외가 발생핬을 때
