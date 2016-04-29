
### 현재 디렉토리와 같은 위치에 있는 디렉토리의 특정 파일 접근
```
auto pathCurrentPath = Poco::Path(getExePath()).makeParent();
auto dataFilePath = pathCurrentPath.popDirectory().append("Data\\Item.csv");
auto dataFile = Poco::File(dataFilePath);

if (!dataFile.exists()){
	return -1;
}
```


### 텍스트 모드로 파일 읽기
```
Poco::FileStream inputStream(dataFilePath.toString(),std::ios::in);
char buf[100] = {0,};

inputStream.getline(buf, 100);

while (inputStream.getline(buf, 100))
{
	...
}

inputStream.close();
```
