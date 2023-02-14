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

openssl을 설치합니다. openssl 디렉터리로 이동한 뒤 설치를 위한 명령어를 입력합니다. 

설치 위치: /data/apache/[openssl 디렉터리]

```bash
cd [설치 위치]
./config -fPIC --prefix=[설치 위치] shared
make && make install
```

### arp 설치

arp를 설치합니다. arp 디렉터리로 이동한 뒤 설치를 위한 명령어를 입력합니다.

설치 위치:  /data/apache/[arp 디렉터리]

```bash
cd [설치 위치]
./configure --prefix=[APR 설치 위치]
make && make insall
```

make 도중 'libtoolT' 오류 발생 시 아래 명령어를 실행합니다. 

```bash
cp -arp libtool libtoolT
```

### arp-util 설치

arp-util를 설치합니다. arp-util 디렉터리로 이동한 뒤 설치를 위한 명령어를 입력합니다.

설치 위치:  /data/apache/[arp-util 디렉터리]

```bash
cd [설치 위치]
./configure --prefix=[설치 위치] --with-apr=[APR 설치 위치] (--with-openssl=[설치 위치])
make && make insall
```

make 도중 expat.h 에서 에러가 발생하면 아래 명령어를 실행합니다.

```bash
yum install expat-devel
```

### pcre 설치

pcre를 설치합니다. pcre 디렉터리로 이동한 뒤 설치를 위한 명령어를 입력합니다.

설치 위치:  /data/apache/[pcre 디렉터리]

```bash
cd [설치 위치]
./configure (--enable-utf8) --prefix=[설치 위치] --with-apr=[ARP 설치 위치]
make && make install
```

### httpd 설치

 위 과정에서 아파치 설치를 위한 필수 라이브러리 설치를 모두 완료했다면 이제 아파치를 설치합니다. httpd 디렉터리로 이동한 뒤 설치를 위한 명령어를 입력합니다.

설치 위치:  /data/apache/[httpd 디렉터리]

```bash
cd [설치 위치]
./configure --prefix=[설치 위치] 
	--enable-mods-shared=all --enable-so --enable-rewrite --enable-http \
--enable-proxy --enable-proxy-http --enable-proxy-ajp --enable-proxy-balaner \
--enable-ssl --enable-ext-filter --enable-proxy-connect --enable-cache \
--enable-deflate --enable-suexec --enable-file-cache  --enable-modules=all \
--with-apr=[ARP 설치 위치] \
--with-apr-util=[ARP-UTILE 설치 위치] \
--with-pcre=[PCRE 설치 위치] \
--with-ssl=[OPENSSL 설치 위치] \
--with-mpm=prefork
make && make install
```

### 일반계정으로 아파치 관리할 수 있도록 설정

일반 계정으로 아파치를 사용하기 위해서는 httpd 실행파일 소유자 및 소유그룹 권한 수정 작업과 httpd 설정 파일 수정 작업이 필요합니다. 각 작업 방법은 아래에서 설명합니다.

http, https 기본 포트인 80, 443 포트를 사용하기 위해서는 root 권한이 필요합니다. 그렇기 때문에 소유그룹의 권한을 사용할 일반 계정으로 내려서 설정해 줍니다. 또한 특수 권한을 부여합니다. httpd 설치 디렉터리 아래에 존재하는 bin 디렉터리로 이동하면 아차피 실행 파일인 httpd 파일이 존재합니다. 해당 파일의 권한 수정 및 특수 권한 부여 작업을 진행합니다.

해당 작업을 위해서는 root 권한이 불가피하게 필요합니다.

```bash
cd /data/apache/httpd-2.4.54
sudo chown root:developer httpd
sudo chmod chmod +s httpd
```

추가로 httpd.conf 파일에서 User와 Group 설정을 일반계정명으로 수정합니다.

```bash
vi /data/apache/httpd-2.4.54/conf/httpd.conf

----------------------------------------------------------------

User developer
Group developer
```

### 아파치 실행 및 확인

이제 아파치 설치 및 설정이 모두 완료되었습니다. 아래 명령어로 아파치를 실행 및 중지하여 사용이 가능합니다.

```bash
//실행 명령어
/data/apache/httpd-2.4.54/httpd -k start

//중지 명령어
/data/apache/httpd-2.4.54/httpd -k stop
```

출처

[https://shonm.tistory.com/614](https://shonm.tistory.com/614)

[https://ansan-survivor.tistory.com/m/120](https://ansan-survivor.tistory.com/m/120)

[https://idsg.tistory.com/13](https://idsg.tistory.com/13)

[https://blog.naver.com/tawoo0/221584084277](https://blog.naver.com/tawoo0/221584084277)
