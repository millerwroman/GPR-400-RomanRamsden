#pragma once

#include <cstdio>
#include <iostream>
#include <thread>

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
	//TestPrime(timer, runTimes, info);
	TestPrimeThreaded(runTimes, info);
	system("pause");
	return 0;
}
