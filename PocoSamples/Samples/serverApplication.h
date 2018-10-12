#pragma once

#include <iostream>

#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco\Util\ServerApplication.h>
#include <Poco/Util/HelpFormatter.h>


class MiniServer : public Poco::Util::ServerApplication
{

protected:

	int main(const std::vector<std::string>& args)
	{
		std::cout << __FUNCTION__ << std::endl;

		// CTRL-C를 누를 때까지 혹은 프로세스가 강제 종료될 때까지 대기
		waitForTerminationRequest();  
				
		return Application::EXIT_OK;
	}

	void initialize(Application& self)
	{
		std::cout << __FUNCTION__ << std::endl;

		loadConfiguration(); // load default configuration files, if present
		ServerApplication::initialize(self);
	}

	void uninitialize()
	{
		std::cout << __FUNCTION__ << std::endl;

		ServerApplication::uninitialize();
	}

	void defineOptions(Poco::Util::OptionSet& options)
	{
		std::cout << __FUNCTION__ << std::endl;

		ServerApplication::defineOptions(options);

		options.addOption(
			Poco::Util::Option("help", "h", "display help information on command line arguments")
			.required(false)
			.repeatable(false));
	}

	void handleOption(const std::string& name, const std::string& value)
	{
		std::cout << __FUNCTION__ << std::endl;

		ServerApplication::handleOption(name, value);
	}

	void displayHelp()
	{
		std::cout << __FUNCTION__ << std::endl;

		Poco::Util::HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader("An echo server implemented using the Reactor and Acceptor patterns.");
		helpFormatter.format(std::cout);
	}
};


void Sample_ServerApplication(int argc, char** argv)
{
	MiniServer app;
	app.run(argc, argv);
}