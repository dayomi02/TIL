## Docker

### Tika 이미지 다운로드

docker pull 명령어를 사용해서 apache tika 이미지 파일을 다운 받는다.

```bash
docker pull apache/tika
```


다운이 완료되면 docker images 명령어로 이미지가 정상적으로 다운되었는지 확인한다.

```bash
docker images
```


이미지가 정상적으로 다운되었으면 docker run 명령어로 Tika 이미지를 사용해서 컨테이너를 실행한다. 명령어 설명은 아래와 같다.

-d  = Detached 모드로 실행하는 옵션. 컨테이너가 백그라운드에서 실행되며, 터미널에 출력이 표시되지 않음.

-p 9998:9998 = 호스트와 컨테이너 간의 포트 매핑을 설정하는 옵션. 호스트의 9998 포트와 컨테이너의 9998 포트를 매핑하여 호스트에서 컨테이너로의 통신을 가능하게 함.

apache/tika:latest = 실행할 docker 이미지의 이름과 태그.

```bash
docker run -d -p 9998:9998 apache/tika:latest
```


실행 로그는 아래와 같다.


이제 Tika 서버의 웹 인터페이스에 접근하여 사용할 수 있게 된 것이다.

## Code

### 예제

HttpClient 를 사용해서 Tika 서버와 통신하여 파일에서 텍스트를 추출하는 작업을 진행했다.

pdf, docx, pptx, xlsx 파일에 대해서 텍스트 추출하는 작업을 테스트 했다. 확장자 별로 ContentType의 값을 다르게 하여 통신해야지 정상적으로 응답 데이터를 얻을 수 있다.

한글 깨짐 문제가 발생하여 “StandardCharsets.UTF_8” 설정을 추가해서 문제를 해결하였다.

```java
package com.dweax.thumbstock.admin.index;

import java.io.File;
import java.nio.charset.StandardCharsets;

import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpPut;
import org.apache.http.entity.ContentType;
import org.apache.http.entity.FileEntity;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.util.EntityUtils;

public class TikaTest {
	
	public static void main(String[] args) {
		System.out.println("TikaTest main 실행");
		
		HttpClient httpClient =  HttpClients.createDefault();
		
		HttpPut request = new HttpPut("http://[Tika가 띄워져 있는 서버 IP]:9998/tika");
		
		try {
			//PDF (pdf) 파일 
			ContentType contentType = ContentType.create("application/pdf", StandardCharsets.UTF_8);
			request.setHeader("Content-Type", contentType.toString());
			
			// Word (docx) 파일
//			ContentType contentTypeWord = ContentType.create("application/vnd.openxmlformats-officedocument.wordprocessingml.document", StandardCharsets.UTF_8);
//			request.setHeader("Content-Type", contentTypeWord.toString());
			
			// PowerPoint (pptx) 파일
//			ContentType contentTypePowerPoint = ContentType.create("application/vnd.openxmlformats-officedocument.presentationml.presentation", StandardCharsets.UTF_8);
//			request.setHeader("Content-Type", contentTypePowerPoint.toString());
			
			// Excel (xlsx) 파일
//			ContentType contentTypeExcel = ContentType.create("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet", StandardCharsets.UTF_8);
//			request.setHeader("Content-Type", contentTypeExcel.toString());
			
			FileEntity fileEntity = new FileEntity(new File("D:\\file.pdf"));
			request.setEntity(fileEntity);
			
			HttpResponse response = httpClient.execute(request);
			
			String responseText = EntityUtils.toString(response.getEntity(), StandardCharsets.UTF_8);
			
			System.out.println("ResponseText : ");
			System.out.println(responseText);

		}catch (Exception e) {
			e.printStackTrace();
		}
	}
}
```

Tika 서버 호출 시 로그 이미지의 맨 마지막 줄과 같이 호출 정보가 로그에 남는다.


추출된 텍스트 데이터를 살펴보면 html 로 작성된 텍스트가 반환 되고 있는 것을 확인할 수 있다. 첨부 파일에서 추출한 데이터를 사용하려면 반환 된 데이터에서 html 소스 코드는 제외하고 사용하는 것이 좋을 것 같다.


참고
https://hub.docker.com/r/apache/tika


추가가
https://dayomi02.tistory.com/12
