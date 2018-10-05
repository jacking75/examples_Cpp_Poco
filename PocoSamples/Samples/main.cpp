#include <iostream>
#pragma comment(lib, "IPHLPAPI.lib")  

#include "iniReader.h"
#include "stopwatch.h"
#include "singletonholder.h"
#include "cache.h"
#include "checksum.h"
#include "dynamicFactory.h"


int main()
{
	//Sample_iniReader();
	//Sample_StopWatch();
	//Sample_SingletonHolder();
	//Sample_LRUCache();
	//Sample_ExpireCache();
	//Sample_Checksum();
	Sample_DynamicFactory();


	getchar();
	return 0;
}


