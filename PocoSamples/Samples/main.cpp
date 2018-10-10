#include <iostream>
#pragma comment(lib, "IPHLPAPI.lib")  

#include "iniReader.h"
#include "stopwatch.h"
#include "singletonholder.h"
#include "cache.h"
#include "checksum.h"
#include "dynamicFactory.h"
#include "workerThread.h"
#include "dateTime.h"
#include "delegate.h"
#include "notificationcenter.h"
#include "environment.h"


int main()
{
	//Sample_iniReader();
	//Sample_StopWatch();
	//Sample_SingletonHolder();
	//Sample_LRUCache();
	//Sample_ExpireCache();
	//Sample_Checksum();
	//Sample_DynamicFactory();
	//Sample_WorkerThread();
	//Sample_DateTime();
	//Sample_Delegate();
	//Sample_NotificationCenter();
	Sample_Environment();

	getchar();
	return 0;
}


