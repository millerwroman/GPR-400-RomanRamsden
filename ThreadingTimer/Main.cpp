#pragma once

#include <cstdio>
#include <iostream>
#include <thread>


#include "BubbleSort.h"
#include "PreformaceTimer.h"
#include "Random.h"



int main()
{
	Timer* timer = new Timer();
	const int runTimes = 1000;
	RunInfo info = RunInfo();
	TestBubbleThreaded(runTimes, info);
	Timer::PrintInfo(info);
	system("pause");
	return 0;
}
