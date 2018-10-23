#pragma once

#include <string>
#include <Poco/Util/IniFileConfiguration.h>



class ServerConfig
{
public:
	bool LoadServerConfig()
	{
		try
		{
			Poco::AutoPtr<Poco::Util::IniFileConfiguration> pZoneServerConf(new Poco::Util::IniFileConfiguration("config_server.ini"));
			m_MaxChannelCount = pZoneServerConf->getInt("ChannelServer.CHANNEL_COUNT");
			m_MaxChannelUserCount = pZoneServerConf->getInt("ChannelServer.CHANNEL_USER_COUNT");
		}
		catch (Poco::FileNotFoundException e) // 파일이 없는 경우
		{
			printf("errer: %s", e.displayText().c_str());
			return false;
		}
		catch (Poco::NotFoundException& e)    // 설정 키워드가 없는 경우
		{
			printf("errer: %s", e.displayText().c_str());
			return false;
		}

		return true;
	}


	int m_MaxChannelCount;
	int m_MaxChannelUserCount;
};


void Sample_iniReader()
{
	std::cout << "[ Sample_iniReader ]" << std::endl;

	ServerConfig config;
	config.LoadServerConfig();

	printf("[%s] ChannelInfo - ChannelCount(%d), UserCount(%d)", __FUNCTION__, config.m_MaxChannelCount, config.m_MaxChannelUserCount);

	std::cout << std::endl << std::endl;
}