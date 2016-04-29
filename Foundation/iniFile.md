

### ini 파일 읽기
ini 파일 형식으로 된 설정 파일을 읽을 때 사용한다.
<pre>
[ZoneServer]
CHANNEL_COUNT = 10
CHANNEL_USER_COUNT = 200
</pre>

```
#include "Poco/Util/IniFileConfiguration.h"

....
try
{
    Poco::AutoPtr<Poco::Util::IniFileConfiguration> pZoneServerConf(new Poco::Util::IniFileConfiguration("test.ini"));
    m_ZoneConfig.nMaxChannelCount       = pZoneServerConf->getInt( "ZoneServer.CHANNEL_COUNT" );
    m_ZoneConfig.nMaxChannelUserCount   = pZoneServerConf->getInt( "ZoneServer.CHANNEL_USER_COUNT" );
}
catch ( Poco::FileNotFoundException e ) // 파일이 없는 경우
{
    SERVER_LOG("Init", LOG_LEVEL::error, "%s", e.displayText().c_str());
    return false;
}
catch ( Poco::NotFoundException& e )    // 설정 키워드가 없는 경우
{
    SERVER_LOG("Init", LOG_LEVEL::error, "%s", e.displayText());
    return false;
}
```
ini 파일 읽기에 실패하는 경우 에외가 발생하므로 예외 처리를 해야 한다(예외 종류에 따라서 실패 이유를 알 수 있다).
