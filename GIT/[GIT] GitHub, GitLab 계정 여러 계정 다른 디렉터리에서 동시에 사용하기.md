#  GitHub, GitLab 계정 여러 계정 다른 디렉터리에서 동시에 사용하기

디렉터리 별로 각각 다른 Git 계정을 사용하기 위한 설정 방법이다.

나는 개인 GitHub 계정과 회사 GitLab 계정을 동시에 사용하고 싶어서 아래와 같이 설정을 진행했다. 요즘에는 Token을 발급 받아서 세팅하는 경우가 많은데 나의 경우는 이미 ssh key로 세팅을 했기 때문에 일단 이렇게 사용하기로 하였다…

1. ssh key 관련 설정
    1. 등록 계정 별로 ssh key 생성
    2. 생성한 ssh-add 등록 (ssh agent 시행 후 ssh key 추가)
    3. 공개키 등록. (생성된 *.pud 를 각각의 계정에 공개키로 등록. gitlab 또는 github 사이트에서 직접 설정하면 된다.)
    
    ssh key 관련 설정의 내용은 아래 블로그의 1-2번 까지의 과정을 보고 진행하였다. 이 때 주의할 점이 있다면 ssh-add를 할 때 window power shell에서 작업하면 안되고 git bash 환경에서 작업해야 한다.
    
    ```bash
    $ ssh-add ~/.ssh/id_rsa_me
    Identity added: /c/Users/xxx/.ssh/id_rsa_me (xxx@gmail.com)
    
    $ ssh-add ~/.ssh/id_rsa_work
    Identity added: /c/Users/xxx/.ssh/id_rsa_work (xxx@xxx.com)
    ```
    
    [[GitHub] 깃허브 여러 계정 사용하기](https://tall-developer.tistory.com/2)
    

1. .gitconfig 설정
    
    기본으로 사용할 계정에 대해서 gitconfig 설정을 한 뒤 추가로 사용할 계정에 대해서 gitconfig 설정을 하면 된다.
    
    1. 기본 gitconfig 설정
        
        `[includeIf]` : ~/gitPersnal 디렉터리에서는 다른 계정을 사용하기 위해 별도의 설정 파일을 사용할 수 있도록 설정하였다.
        
        ```
        # .gitconfig 파일 내용
        
        [user]
                email = 기본 계정 이메일
                name = 기본 계정 이름
        
        [core]
                sshCommand = "ssh -i ~/.ssh/id_rsa_work"
        
        [includeIf "gitdir:~/gitPersnal/"]
                path = ~/.gitconfig-persnal
        ```
        
    2. 추가 gitconfig 설정
        
        ```
        # .gitconfig-persnal 파일 내용
        
        [user]
            email = 추가 계정 이메일
            name = 추가 계정 이름
        
        [github]
            user = 추가 계정명
        
        [core]
            sshCommand = "ssh -i ~/.ssh/id_rsa_me"
        
        ```
        
    
출처 : [[Git] macOS에서 Github 계정과 GitLab 계정을 폴더(Directory)별로 사용하자 (tistory.com)](https://livenow14.tistory.com/83), [mrchypark: 여러개의 github 계정을 사용해보자](https://mrchypark.github.io/post/%EC%97%AC%EB%9F%AC%EA%B0%9C%EC%9D%98-github-%EA%B3%84%EC%A0%95%EC%9D%84-%EC%82%AC%EC%9A%A9%ED%95%B4%EB%B3%B4%EC%9E%90/), [[GitHub] 깃허브 여러 계정 사용하기 (tistory.com)](https://tall-developer.tistory.com/2)
