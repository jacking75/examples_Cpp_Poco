//출처: http://poco.roundsquare.net/2010/04/29/pocostopwatch/

#pragma once
#include <thread>

#include <Poco/Stopwatch.h>


void Sample_StopWatch()
{
	Poco::Stopwatch watch;

	std::cout << "시간 측정 시작" << std::endl;

	watch.start();
	
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	watch.stop();

	// microseconds, seconds 단위로만 측정 가능
	printf("[%s] 걸린 시간 (%I64d)microseconds, (%d)seconds", __FUNCTION__, watch.elapsed(), watch.elapsedSeconds());
}