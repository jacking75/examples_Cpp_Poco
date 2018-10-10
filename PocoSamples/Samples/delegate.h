#pragma once

#include <Poco/BasicEvent.h>
#include <Poco/Delegate.h>
#include <Poco/Format.h>

#include <string>
#include <vector>

const int kNumTargets = 3;

struct TargetArgs
{
	int			val;
};

class Source
{
public:
	Poco::BasicEvent<TargetArgs>	m_Event;

	Source(){ }

	void notify(TargetArgs args)
	{
		m_Event(this, args);
	}

	std::string name(void) const
	{
		return std::string("source");
	}
};

class Target
{
public:
	Target(int id) :
		m_ID(id)
	{
	}

	void onEvent(const void* pSender, TargetArgs& args)
	{
		int valOriginal = args.val;
		++args.val;
		std::cout << Poco::format(" Target[%d]::onEvent (got data=%d from %s -> %d)"
			, m_ID
			, valOriginal
			, const_cast<Source*>(reinterpret_cast<const Source*>(pSender))->name()
			, args.val) << std::endl;
	}

private:
	int	m_ID;
};


void TestBasicEvent()
{
	std::cout << "--- Basic Event ---" << std::endl;

	Source source;

	std::vector<Target*> targets(kNumTargets);
	for (int i = 0; i < kNumTargets; ++i)
	{
		targets[i] = new Target(i);
		source.m_Event += Poco::delegate(targets[i], &Target::onEvent);
	}

	TargetArgs args = { 12 };
	source.notify(args);


	for (int i = kNumTargets - 1; i >= 0; --i)
	{
		source.m_Event -= Poco::delegate(targets[i], &Target::onEvent);
		delete targets[i];
	}
}

void TestExpireingTarget()
{
	std::cout << "--- Expireing Target ---" << std::endl;

	Source source;
	Target target(0);

	source.m_Event += Poco::delegate(&target, &Target::onEvent, 100);

	TargetArgs args = { 34 };
	source.notify(args);

	Poco::Thread::sleep(200);

	args.val = 56;
	source.notify(args);	// it's already expired -> no output
}

void TestAsyncNotify()
{
	std::cout << "--- Async Notify ---" << std::endl;

	Poco::BasicEvent<TargetArgs>* pSource = reinterpret_cast<Poco::BasicEvent<TargetArgs>*>(new Source);
	Target target(0);
	(*pSource) += Poco::delegate(&target, &Target::onEvent);
	
	TargetArgs args = { 78 };
	// 이벤트 함수 호출 완료를 기다리지 않고 바로 리턴한다.
	// 이벤트 함수는 다른 스레드에서 실행한다.
	Poco::ActiveResult<TargetArgs> retArg = pSource->notifyAsync(&target, args); 
	delete pSource; // must work even when the event got deleted!
	pSource = NULL;

	retArg.wait();
}

void Sample_Delegate()
{	
	TestBasicEvent();
	TestExpireingTarget();
	TestAsyncNotify();
}