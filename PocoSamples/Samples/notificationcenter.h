#pragma once

#include <Poco/Format.h>
#include <Poco/NotificationCenter.h>
#include <Poco/Observer.h>

#include <string>


class BaseNotification : public Poco::Notification
{
public:
	BaseNotification(int data) :
		m_data(data)
	{
	}

	int data() const
	{
		return m_data;
	}

private:
	int	m_data;
};


class ObserverWorker
{
public:	
	ObserverWorker() = default;

	ObserverWorker(std::string name)
	{
		m_Name = name;
	}

	void handleNotification(Poco::Notification* pNf)
	{
		Poco::AutoPtr< BaseNotification > pNotification = dynamic_cast<BaseNotification*>(pNf);
		if (pNotification)
		{
			std::cout << Poco::format("%s - handleNotification got BaseNotification(%d)\n", m_Name, pNotification->data());			
		}
	}

	void handleNotification2(BaseNotification* pNf)
	{
		std::cout << Poco::format("%s - handleNotification got BaseNotification2(%d)\n", m_Name, pNf->data());
	}

private:
	std::string m_Name;
};

void Sample_NotificationCenter()
{
	std::cout << "[ Sample_NotificationCenter ]" << std::endl;

	Poco::NotificationCenter nc;

	ObserverWorker worker1(std::string("worker1"));
	ObserverWorker worker2(std::string("worker2"));
	ObserverWorker worker3(std::string("worker3"));
		
	nc.addObserver(Poco::Observer<ObserverWorker, Poco::Notification>(worker1, &ObserverWorker::handleNotification));
	nc.addObserver(Poco::Observer<ObserverWorker, Poco::Notification>(worker2, &ObserverWorker::handleNotification));
	nc.addObserver(Poco::Observer<ObserverWorker, BaseNotification>(worker3, &ObserverWorker::handleNotification2));


	nc.postNotification(new BaseNotification(0));	
	nc.postNotification(new BaseNotification(1));	
	nc.postNotification(new BaseNotification(2));

	std::cout << std::endl << std::endl;
}