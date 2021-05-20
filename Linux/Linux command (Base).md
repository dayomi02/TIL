## 꼭 알아야할 리눅스 기본 명령어 10가지

1. ls - 현재 위치 파일목록을 조회하는 명령어
2. cd - 디렉토리를 이동하는 명령어
3. touch - 파일의 용량이 0인 파일을 생성, 날짜 변경하는 명령어
4. mkdir - 디렉토리를 생성하는 명령어
5. cp - 파일을 복사하는 명령어
6. mv - 파일을 이동시키는 명령어
7. rm - 파일을 제거하는 명령어
8. cat - 파일의 내용을 화면에 출력하거나 파일을 만드는 명령어
9. redirection - 화면에 출력되는 결과를 파일로 저장하는 명령어
10. alias - 자주 수행하는 명령어들을 쉽게 사용할 수 있도록 설정하는 명령어

## 01. ls (list segments)

ls는 현재 위치의 파일 목록을 조회하는 명령어 입니다.

주요 옵션으로는

ls -l : 파일들의 상세정보를 나타냅니다.

ls -a : 숨어있는 파일들도 표시합니다.

ls -t : 파일들을 생성된 시간별로(최신것 부터) 표시합니다.

ls -rt : 파일들을 오래된 시간부터 표시합니다.

ls -F : 파일을 표시할 때 마지막에 유형을 나타내는 파일명을 끝에 표시합니다.
('/'- 디렉토리, '*' - 실행 파일, '@' - 링크 )

각 옵션들은 자유자재로 합성해서 사용가능합니다.

ex) ls -lrt : 파일들의 상세정보를 나타내며, 오래된 것부터 표시합니다.

## 02. cd (change directory)

cd는 경로를 이동할 때 사용하는 명령어 입니다.

cd~ : 어느 곳에든지 홈디렉토리로 바로 이동합니다.

cd.. : 상위 디렉토리로 이동합니다.

cd /dir : 절대경로 dir로 이동할 경우 사용합니다.

cd - : 이동하기 바로 전의 디렉토리로 이동합니다.

## 03. touch

touch는 파일의 용량이 0인 파일을 생성, 날짜를 변경하는 명령어 입니다.

touch filename : filename의 파일을 생성합니다.

touch -c filename : filename의 시간을 현재시간으로 변경합니다.

touch -t 100001011200 filename : filename의 시간을 날짜정보(YYYYMMDDhhmm)로 변경합니다.

touch -r filename1 filename2 : filename2의 날짜정보를 filename1의 날짜정보와 같게 변경합니다.

## 04. mkdir (make directory)

mkdir은 새로운 디렉토리를 만들 때 사용하는 명령어입니다.

mkdir dirname : dirname의 디렉토리를 생성합니다.

mkdir -p dirname/subdname : 존재하지 않는 하위디렉토리까지 생성합니다.

mk -m 644 dirname : 특정 퍼미션을 갖는 디렉토리를 생성합니다.

## 05. cp (copy)

cp는 파일을 복사하는 명령어입니다.

cp file cfile : file을 cfile이라는 이름으로 복사합니다.

cp -f file cfile : 복사할 때 복사대상이 있으면 자우고 강제로 복사합니다.

cp -R dir cdir : 디렉토리 복사할 때 사용하여, 폴더안의 모든 하위경로와 파일들을 모두 복사합니다.

## 06. mv (move)

mv는 파일을 이동하는 명령어 입니다. cp와 비슷하지만 다른 점은 cp는 파일을 복사하여 원본 파일이 남아있지만 mv는 원본 파일이 남지 않는다는 점입니다. 그래서 이름 변경시에도 사용가능합니다.

mv fname mfname : fname의 파일을 mfname의 이름으로 이동/변경 합니다.

mv -b fname mfname : mfname의 파일이 존재하면 mfname을 백업한 뒤에 이동합니다.

mv -f fname mfname : mfname의 파일이 존재하면 백업 없이 덮어씁니다.

## 07. rm (list segments)

rm은 파일이나 디넥토리를 삭제할 때 사용하는 명령어 입니다.

rm fname : fname을 삭제합니다.

rm -f fname : fname을 묻지 않고 삭제합니다.

rm -r dir : dir을 삭제합니다.

디렉토리는 -r 옵션 없이는 삭제할 수 없습니다.

## 08. cat (catenate)

cat은 파일이름을 인자로 받아서 그 내용을 출력할 때 사용합니다.

cat fname : fname의 내용을 출력합니다.

cat fname1 fname2 : fname1과 fname2의 내용을 이어서 출력합니다.

cat fname1 fname2 | more : fname1, fname2를 출력하는데 페이지별로 출력합니다.

cat fname1 fname2 | head : fname1, fname2를 출력하는데 처음부터 10번째까지만 출력합니다.

cat fname1 fname2 | tail : fname1, fname2를 출력하는데 끝에서부터 10번째까지만 출력합니다.

## 09. redirection ( '>', '>>')

redirection은 리눅스 스트림의 방향을 조정하는 명령어 입니다.

명령 > 파일 : 명령의 결과를 파일로 저장합니다.
cat fname1 fname2 > fname3 : fname1, fname2를 출력하고 fname3 이라는 파일에 저장합니다.

명령 >> 파일 : 명령의 결과를 파일에 추가합니다.
cat fname4 >> fname3 : fname3에 fname4의 내용을 추가합니다.

명령 < 파일 : 파일의 데이터를 명령에 입력합니다.
cat < fname1 : fname의 내용을 출력합니다.

ex) cat < fname1 > fname2 : fname1의 내용을 출력하는 결과물을 fname2에 저장합니다.

## 10. alias

alias는 자주 사용하는 명령어를 간단한 명령어로 설정하는 명령어 입니다. 해제하고자 하는 경우에는 un alias를 사용합니다.

alias new = 'command' : command를 실행하는 새 명령어 new를 만듭니다.
ex) alias ls = 'ls -l' : ls를 실행하면 -l 옵션을 갖는 ls를 실행합니다.

alias : 현재 alias 목록을 출력합니다.

unalias new : new라는 alias를 해제합니다.
