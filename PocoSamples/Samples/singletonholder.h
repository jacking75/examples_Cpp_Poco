//√‚√≥: http://poco.roundsquare.net/2010/07/21/pocosingletonholder/

#pragma once

#include <Poco/SingletonHolder.h>

class SingletonTarget
{
public:
	SingletonTarget()
	{
		std::cout << "SingletonTarget created." << std::endl;
	}

	~SingletonTarget()
	{
		std::cout << "SingletonTarget deleted." << std::endl;
	}

	SingletonTarget(const SingletonTarget&) = delete;
	SingletonTarget& operator = (const SingletonTarget&) = delete;


	void doSomething(void)
	{
		std::cout << "SingletonTarget::doSomething called." << std::endl;
	}

};

class ClassWithDefaultInstance
{
public:
	ClassWithDefaultInstance()
	{
		std::cout << "ClassWithDefaultInstance created." << std::endl;
	}

	~ClassWithDefaultInstance()
	{
		std::cout << "ClassWithDefaultInstance deleted." << std::endl;
	}

	ClassWithDefaultInstance(const ClassWithDefaultInstance&) = delete;
	ClassWithDefaultInstance& operator = (const ClassWithDefaultInstance&) = delete;

	void doSomething(void)
	{
		std::cout << "ClassWithDefaultInstance::doSomething called." << std::endl;		
	}

	static ClassWithDefaultInstance& defaultInstance()
	{
		static Poco::SingletonHolder<ClassWithDefaultInstance> sh;
		return *sh.get();
	}

private:
};

void Sample_SingletonHolder()
{
	std::cout << "[ Sample_SingletonHolder ]" << std::endl;

	{
		std::cout << " --- SingletonTarget ---" << std::endl;
		Poco::SingletonHolder<SingletonTarget> singleton;
		singleton.get()->doSomething();
		singleton.get()->doSomething();
	}
	{
		std::cout << " --- ClassWithDefaultInstance ---" << std::endl;
		ClassWithDefaultInstance::defaultInstance().doSomething();
		ClassWithDefaultInstance::defaultInstance().doSomething();
	}

	std::cout << std::endl << std::endl;
}