## 개요
- 다운로드: http://pocoproject.org/download/index.html
- 문서: http://pocoproject.org/documentation/index.html


## Windows
- VS2010, x64, static lib 으로 빌드
    - buildwin.cmd 100 build static_mt both x64 samples tests devenv
    - 이렇게 빌드하면 PocoFoundation만 빌드 된다. 그래서 Util, XML, Net, MongoDB 등을 직접 빌드해야 한다.
    - Util 등의 라이브러리 디렉토리에 VS 버전, 32 or 64 플랫폼별 VS 프로젝트 파일이 있다.
    - 모두 빌드가 완료되면 lib64 디렉토리에 만들어져 있다.
- VS2015, static mt, debug/release, x64 로 빌드
    - buildwin.cmd 140 rebuild static_mt both x64
- VS2015, static md, debug/release, x64 로 빌드
    - buildwin.cmd 140 rebuild static_md both x64
- OpenSSL 빌드
    - openssl-1.0.2을 플랫폼 별로 빌드한다. D:/Libraries/openssl-1.0.2-x86 と D:/Libraries/openssl-1.0.2-x64
    - components 파일을 열어서 OpenSSL 관련 디렉토리를 위의 디렉토리로 변경한다. set OPENSSL_DIR=D:\Libraries\openssl-1.0.2-x64
- 생성된 lib 파일과 헤더 파일 디렉토리로 VS 프로젝트 설정에 등록한다.
 
<img src="resource\PocoVCInclude.png">  
<img src="resource\PocoVCLib.png">
  
<br>  
<br>  
<br> 
<br>

  
## Linux

공식 사이트에서 최신 버전을 다운로드 한다.
압축을 풀고, 빌드한다. 
  
아래는 64비트, static 라이브러리, 테스트와 샘플은 제외 하는 설정으로 빌드 한다
<pre>
$ tar zxvf poco-1.7.8p2-all.tar.gz
$ cd poco-1.7.8p2-all/
 
$ export OSARCH_64BITS=1
$ ./configure --static --no-tests --no-samples
$ make
</pre>

설정 정보는 아래 처럼 더 추가할 수 있다.
<pre>
./configure --omit=Data/ODBC,Data/SQLite --prefix=/usr --cflags=-fPIC --cflags=-std=c++11 --static --shared  --no-tests --no-samples
</pre>

빌드가 끝나면 아래 디렉토리에 라이브러리가 만들어져 있다.
<pre>
lib/Linux/x86_64
</pre>
 
디버그 버전은 라이브러리 이름 뒤에 'd'가 붙고, 64비트 버전은 뒤에 '64'가 붙는다.  


### 샘플 예제
sample.cpp
```
#include <iostream>
#include <Poco/RegularExpression.h>

int main() {
    Poco::RegularExpression regexp("^[a-zA-Z]+");

    std::string buf;
    regexp.extract("ABC123", buf);
    std::cout << buf << std::endl; //=> ABC

    return 0;
}
```

Makefile
```
CXX=g++
CXXFLAGS=-I/mnt/e/linux/dev/c++/thirdparty/poco/Foundation/include
LDFLAGS=-L/mnt/e/linux/dev/c++/thirdparty/poco/lib/Linux/x86_64
LDLIBS=-lPocoFoundation64

all:sample

clean:
	rm -rf sample
	rm -rf *.o
```
  
<br>  
<br>  

### 예제 돌려보기

http://knoow.tistory.com/74  
http://scriptlabo.blog26.fc2.com/blog-entry-35.html  
https://www.qoosky.io/techs/8e92d3d34a  

