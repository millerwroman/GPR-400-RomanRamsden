#pragma once

#include <cstdio>
#include <iostream>
#include <thread>


#include "BubbleSort.h"
#include "GameOfLife.h"
#include "PreformaceTimer.h"
#include "PrimeFactorization.h"
#include "Random.h"
#include "vector"



int main()
{
	Timer* timer = new Timer();
	const int runTimes = 10000;
	RunInfo info = RunInfo();

	TestPrimeThreaded(runTimes, info);
	Timer::PrintInfo(info);
	system("pause");
	return 0;
}
