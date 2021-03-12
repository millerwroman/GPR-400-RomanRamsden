#pragma once
#include "PreformaceTimer.h"
#include "WorkerThread.h"
#include <atomic>

void Print(std::vector<int> vec)
{
	for (auto i : vec)
	{
		printf("%i", i);
	}
}

//Implementation of the "Vishwas Garg" method
//Known as the simplest implementation of a prime factorization algorithms 
std::vector<int> FactorPrimes(long long n)
{
	std::vector<int>::iterator it;
	std::vector<int> primes;

	while (n % 2 == 0)
	{
		it = primes.end();
		primes.insert(it, 2);
		n = n / 2;
	}

	for (int i = 3; i <= sqrt(n); i = i + 2)
	{
		while (n % i == 0)
		{
			it = primes.end();
			primes.insert(it, 2);
			n = n / i;
		}
	}

	if (n > 2)
	{
		it = primes.end();
		primes.insert(it, n);
	}
	return primes;
}

void TestPrime(Timer* timer, int runTimes, RunInfo& info)
{
	const long long numberToFactor = (long long)GetRandomFloat32_Range(4 * 10000000, (6 * 10000000));
	std::vector<int> finalRun;
	for (int i = 0; i < runTimes; ++i)
	{
		timer->StartTimer("Prime");
		finalRun = FactorPrimes(9223372036854775807);
		float timeTaken = timer->StopTimer("Prime");
		info.averageTime += timeTaken;
		info.minTime = (timeTaken < info.minTime ? timeTaken : info.minTime);
		info.maxTime = (timeTaken > info.maxTime ? timeTaken : info.maxTime);
	}
	info.averageTime /= runTimes;

	printf("\n\nRuntime Info: \n");
	printf("Number Factored: %u \n", (unsigned int)numberToFactor);
	printf("Max Time: %f \n", info.maxTime);
	printf("Min Time: %f \n", info.minTime);
	printf("Average Time: %f \n", info.averageTime);
	printf("Sample Size: %i \n", runTimes);
	Print(finalRun);
}


void TestPrimeThreaded(int runTimes, RunInfo& info)
{
	const unsigned int MAX_THREADS = 16;
	std::vector<WorkerThread*> threadList;
	totalRuns = runTimes;
	for (int i = 0; i < MAX_THREADS; ++i)
	{
		threadList.push_back(new WorkerThread());
	}

	numberThreadsStarted = 0;
	for (int i = 0; i < (runTimes < threadList.size() ? runTimes : threadList.size()); ++i)
	{
		numberThreadsStarted++;
		threadList[i]->FactorNumbers(9223372036854775807);
	}

	do
	{
		Sleep(1);
		std::cout << "Working! " << std::endl;
		if (numberThreadsStarted < runTimes && numberThreadsActive < MAX_THREADS)
		{
			numberThreadsStarted++;
		}
	} while (numberThreadsActive > 0 || numberThreadsStarted == 0);

	info = WorkerThread::GetRunInfo();
}

/*Questions:
 *Async?
 *Return from threads?
 *Better timer?
 *Atomic Function?
*/