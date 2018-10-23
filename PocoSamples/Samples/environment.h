#pragma once

#include <Poco/Environment.h>
#include <Poco/Format.h>

#include <string>


const std::string kShellStr("SHELL");
const std::string kNotExistStr("NOT_EXIST");
const std::string kNotExistDefaultStr("NOT_EXIST_DEFAULT");
const std::string kManPathStr("MANPATH");

void Sample_Environment()
{
	std::cout << "[ Sample_Environment ]" << std::endl;

	// Poco::Environment::get
	try
	{
		std::cout << Poco::format("          %s: %s", kShellStr, Poco::Environment::get(kShellStr)) << std::endl;
	}
	catch (Poco::NotFoundException& exc)
	{
		std::cout << exc.displayText() << std::endl;
	}
	std::cout << Poco::format("      %s: %s", kNotExistStr, Poco::Environment::get(kNotExistStr, kNotExistDefaultStr)) << std::endl;

	// Poco::Environment::has
	std::cout << Poco::format("    has %s: %s", kManPathStr, std::string(Poco::Environment::has(kManPathStr) ? "yes" : "no")) << std::endl;


	// Poco::Environment::nodeId. 이더넷카드 MAC Address
	try
	{
		Poco::Environment::NodeId nodeId;
		Poco::Environment::nodeId(nodeId);
		std::cout << Poco::format("         nodeId: %02?x:%02?x:%02?x:%02?x:%02?x:%02?x"
			, nodeId[0]
			, nodeId[1]
			, nodeId[2]
			, nodeId[3]
			, nodeId[4]
			, nodeId[5]) << std::endl;
	}
	catch (Poco::SystemException& exc)
	{
		std::cout << exc.displayText() << std::endl;
	}
	std::cout << Poco::format("         nodeId: %s", Poco::Environment::nodeId()) << std::endl;

	// Poco::Environment::nodeName. 컴퓨터 이름
	std::cout << Poco::format("       nodeName: %s", Poco::Environment::nodeName()) << std::endl;

	// Poco::Environment::osArchitecture
	std::cout << Poco::format(" osArchitecture: %s", Poco::Environment::osArchitecture()) << std::endl;

	// Poco::Environment::osName
	std::cout << Poco::format("         osName: %s", Poco::Environment::osName()) << std::endl;

	// Poco::Environment::osVersion
	std::cout << Poco::format("      osVersion: %s", Poco::Environment::osVersion()) << std::endl;

	// Poco::Environment::processorCount
	std::cout << Poco::format(" processorCount: %u", Poco::Environment::processorCount()) << std::endl;

	std::cout << std::endl << std::endl;
}