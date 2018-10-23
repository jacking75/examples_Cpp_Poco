#pragma once

#include <Poco/Thread.h>

#include <Poco/LRUCache.h>
#include <Poco/ExpireCache.h>

void Sample_LRUCache()
{
	std::cout << "[ Sample_LRUCache ]" << std::endl;

	Poco::LRUCache<int, int> aCache(3);
	aCache.add(1, 2);
	aCache.add(3, 4);
	aCache.add(5, 6);

	auto size = aCache.size();
	auto allKeys = aCache.getAllKeys();
	printf("cache size: %zd\n", size);
	for (auto key : allKeys)
	{
		std::cout << key << std::endl;
	}


	aCache.get(1);
	aCache.get(5);

	aCache.add(15, 16);
	
	size = aCache.size();
	allKeys = aCache.getAllKeys();
	printf("cache size: %zd\n", size);
	for (auto key : allKeys)
	{
		std::cout << key << std::endl;
	}

	std::cout << std::endl << std::endl;
}


void Sample_ExpireCache()
{
	std::cout << "[ Sample_ExpireCache ]" << std::endl;

	auto expireTime = 250; // 밀리세컨드
	Poco::ExpireCache<int, int> aCache(expireTime);
	
	aCache.add(1, 2);
	aCache.add(3, 4);
	
	auto size = aCache.size();
	auto allKeys = aCache.getAllKeys();
	printf("cache size: %zd\n", size);
	for (auto key : allKeys)
	{
		std::cout << key << std::endl;
	}

	
	Poco::Thread::sleep(expireTime + 20);
	
	aCache.add(5, 6);

	size = aCache.size();
	allKeys = aCache.getAllKeys();
	printf("cache size: %zd\n", size);
	for (auto key : allKeys)
	{
		std::cout << key << std::endl;
	}

	std::cout << std::endl << std::endl;
}