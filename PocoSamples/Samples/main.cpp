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
	Sample_DateTime();

	getchar();
	return 0;
}


