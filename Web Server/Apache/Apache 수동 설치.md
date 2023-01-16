# Apache 수동 설치

아파치 수동 설치 방법에 대해서 설명합니다.

여러 시행착오 끝에 최종적으로 아파시 실행에 성공한 설치 방법에 대해 적어보려고 합니다.

폐쇄망 환경에서 아파치 수동 설치를 진행하였으며, 설치 계정 및 실행 계정은 일반 계정을 사용하였습니다, root 권한이 필요한 일부 명령어는 따로 정리하였습니다.

작업 순서는 아래와 같습니다.

1. 아파치 설치를 위한 필수 패키지 설치
2. 아파치 설치 디렉터리 생성
3. 필요 라이브러리 복사 및 압축 해제
4. openssl  설치
5. arp 설치
6. arp-util 설치
7. pcre 설치
8. httpd 설치
9. 일반계정으로 아파치 관리할 수 있도록 설정
10. 아파치 config 세팅
11. 아파치 실행 및 확인

### 아파치 설치를 위한 필수 패키지 설치

필요 라이브러리 및 httpd 설치를 위한 필수 패키지를 설치합니다. 해당 명령어는 root  계정 또는 권한이 부여된 계정에서 실행해야 합니다.

설치가 필요한 필수 패키지 목록은 아래와 같습니다.

- gcc
- apr
- apr-devel
- apr-util
- apr-util-devel
- pcre-devel
- zlib-devel
- perl
- perl-Test-Harness
- perl-Test-Simple
- openssl-devel

```bash
yum install [패키지명]
```

### 아파치 설치 디렉터리 생성

아파치 설치를 진행할 디렉터리를 생성합니다. 저는 /data/apache 디렉터리를 아파치 설치 디렉터리로 사용하였습니다.

```bash
cd /data
mkdir apache
```

### 필요 라이브러리 복사 및 압축 해제

아파치 설치를 위해 필수로 설치해야 하는 라이브러리가 있습니다. 필요 라이브러리 파일들은 설치 파일을 직접 다운받아 서버에 업로드 합니다. 

- openssl
    
    [https://www.openssl.org/source/](https://www.openssl.org/source/)
    
- arp
    
    [https://apr.apache.org/download.cgi](https://apr.apache.org/download.cgi)
    
- arp-util
    
    [https://apr.apache.org/download.cgi](https://apr.apache.org/download.cgi)
    
- pcre
    
    [https://www.pcre.org/](https://www.pcre.org/)
    
- httpd
    
    [https://httpd.apache.org/download.cgi#apache24](https://httpd.apache.org/download.cgi#apache24)    

서버에 업로드 후 아파치 설치 디렉터리 경로 아래에 모두 압축해제 합니다. 꼭 아파치 설치 디렉터리 경로(/data/apache) 아래에 압축해제할 필요는 없습니다. 하지만 소스 관리를 위해 아파치 설치 디렉터리 아래에 모두 압축해제 하였습니다.

```bash
tar zxvf [필요 라이브러리 압축 파일 명]
```

### openssl  설치

### arp 설치

### arp-util 설치

### pcre 설치

### httpd 설치

### 일반계정으로 아파치 관리할 수 있도록 설정

### 아파치 config 세팅

### 아파치 실행 및 확인

출처

[https://shonm.tistory.com/614](https://shonm.tistory.com/614)

[https://ansan-survivor.tistory.com/m/120](https://ansan-survivor.tistory.com/m/120)

[https://idsg.tistory.com/13](https://idsg.tistory.com/13)

[https://blog.naver.com/tawoo0/221584084277](https://blog.naver.com/tawoo0/221584084277)
