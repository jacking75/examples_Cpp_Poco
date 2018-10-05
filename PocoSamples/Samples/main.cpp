#include <iostream>
#pragma comment(lib, "IPHLPAPI.lib")  

#include "iniReader.h"
#include "stopwatch.h"
#include "singletonholder.h"
#include "cache.h"


int main()
{
	//Sample_iniReader();
	//Sample_StopWatch();
	//Sample_SingletonHolder();
	//Sample_LRUCache();
	Sample_ExpireCache();

	getchar();
	return 0;
}


