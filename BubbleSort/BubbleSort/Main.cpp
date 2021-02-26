#pragma once
#include <cstdio>
#include <iostream>

#include "PreformaceTimer.h"
#include "Random.h"
#include "GameOfLife.h"
#include "BubbleSort.h"
#include "PrimeFactorization.h"
#include  "vector"


int main()
{
	Timer* timer = new Timer();
	const int runTimes = 1000;
	RunInfo info = RunInfo();

	
	//BubbleSortTest(timer, runTimes, info);
	//TestPrime(timer, runTimes, info);
	//GameOfLifeTest(timer);

	
	
	system("pause");
	return 0;
}