#pragma once

#include <Poco/Checksum.h>

void Sample_Checksum()
{
	char buffer[] = { "0123456789" };

	Poco::Checksum checker1(Poco::Checksum::TYPE_ADLER32);
	checker1.update(buffer, 10);

	std::cout << checker1.checksum() << std::endl;


	Poco::Checksum checker2(Poco::Checksum::TYPE_CRC32);
	checker2.update(buffer, 10);

	std::cout << checker2.checksum() << std::endl;
}