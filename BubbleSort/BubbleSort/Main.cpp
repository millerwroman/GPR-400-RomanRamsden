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
	const int runTimes = 1000;
	RunInfo info = RunInfo();

	//std::thread thread(Task, 1);

	//BubbleSortTest(timer, runTimes, info);
	// TestPrime(timer, runTimes, info);
	// GameOfLifeTest(timer);
	TestPrimeThreaded(timer, runTimes, info);

	system("pause");
	return 0;
}
