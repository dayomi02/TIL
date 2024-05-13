# Docker Root Dir 수정하기

docker의 기본 저장소를 변경하는 방법은 매우 간단하다. 서비스 중지 후 설정 파일을 수정한 뒤 다시 서비스를 기동하면 된다.

도커 기본 저장소는 `docker info` 명령어를 통해서 확인할 수 있다. 도커를 설치하면 자동으로 **/var/lib/docker** 디렉터리가 기본 저장소로 설정되고, 도커 관련 파일이 해당 디렉터리 아래에 모두 저장된다. 

기본 저장소 용량이 가득 찼을 때나, 내가 임의로 도커 저장소를 지정하고 싶은 경우 그렇게 할 수 있다. 변경 방법은 아래에 순서대로 설명한다. 명령어는 리눅스를 기준으로 작성하였다.

1. 실행 중인 도커 데몬의 Docker Root Dir 확인하기
    
    변경하기 전에 우선 현재 디렉터리를 확인해야 한다. 변경 후 정상적으로 변경되었는지도 확인이 가능하기 때문이다.
    
    ```bash
    docker info | grep "Root Dir"
    ```
    
2. 도커 데몬 중지하기
    
    실행 중인 도커를 중지한다. stop 으로 중지한 후 status 로 정상적으로 종료되었는지 확인할 수 있다.
    
    ```bash
    systemctl stop docker.service
    ```
    
    ```bash
    systemctl status docker.service
    ```
    
3. 설정 파일 수정하기 (daemon.json)
    
    수정할 Root Dir 에 대한 정보를 파일에 추가해주면 된다. 파일 위치는 /etc/docker/daemon.json 경로이다. 해당 디렉터리에 설정 파일이 존재하지 않는다면 파일을 생성하여 작성해주면 된다. 이미 설정 파일이 있다면 기존 내용에 추가만 해주면 된다.
    
    ```bash
    vi /etc/docker/daemon.json
    ```
    
    ```bash
    {
        "data-root": "/home/docker/data"
    }
    ```
    
4. 기존 데이터 복사하기
    
    기존 Root Dir 위치에 있던 파일을 수정할 Root Dir 위치로 복사하거나 이동해야 한다. 그렇지 않으면 이미지나 볼륨 데이터 등 기존에 사용하고 있던 데이터를 사용하지 못한다. 도커를 설치한 뒤 바로 수정하는 경우가 아니고, 기존에 도커를 사용하다가 수정할 경우에는 해당 내용을 주의해야 한다.
    
    ```bash
    mv /var/lib/docker /home/docker/data
    ```
    
5. 도커 데몬 실행하기
    
    설정 파일 수정 및 기존 데이터 복사 작업이 모두 완료되었다면 이제 다시 도커를 실행시키면 된다. 중지하기와 마찬가지로 status 명령어로 정상적으로 실행되었는지 확인할 수 있다.
    
    ```bash
    systemctl start docker.service
    ```
    

출처: [docker : data root directory 변경하기](https://jinane.tistory.com/45)
