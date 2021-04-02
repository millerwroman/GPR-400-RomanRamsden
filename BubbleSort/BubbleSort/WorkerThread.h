#include <process.h>
#include "PrimeFactorization.h"

static unsigned int numberThreadsActive = 0;
static unsigned int numberThreadsStarted = 0;
std::atomic_int currentCount(0);
std::atomic_int totalRuns(0);
static InstanceInfo info[10000];

void ThreadedFactor(void* input)
{
	numberThreadsActive++;

	long long val = reinterpret_cast<long long>(input);
	long long valInital = val;
START:
	info[currentCount].StartTime = Timer::GetTime();
	std::vector<int>::iterator it;
	std::vector<int> primes;

	while (val % 2 == 0)
	{
		it = primes.end();
		primes.insert(it, 2);
		val = val / 2;
	}

	for (int i = 3; i <= sqrt(val); i = i + 2)
	{
		while (val % i == 0)
		{
			it = primes.end();
			primes.insert(it, 2);
			val = val / i;
		}
	}

	if (val > 2)
	{
		it = primes.end();
		primes.insert(it, val);
	}
	info[currentCount].EndTime = Timer::GetTime();
	if (currentCount < totalRuns)
	{
		++currentCount;
		goto START;
	}
	numberThreadsActive--;
}



class WorkerThread
{
public:
	WorkerThread() {};
	~WorkerThread() {};

	static void FactorNumbers(long long val)
	{
		_beginthread(ThreadedFactor, 0, &val);
	}

	static void ThreadedBubble()
	{
		
	}

	static RunInfo GetRunInfo()
	{
		return Timer::ProcessInstanceArray(info, 10000);
	}

	static void Reset()
	{
		numberThreadsActive = 0;
		numberThreadsStarted = 0;
		currentCount = 0;
		totalRuns = 0;
	}
};


//void ThreadedBubble(void* val, const int size)
//{
//	numberThreadsActive++;
//	int* arr = reinterpret_cast<int*>(val);
//
//	for (int i = 0; i < size - 1; ++i)
//	{
//		for (int j = 0; j < size - i - 1; ++j)
//		{
//			if (arr[j] > arr[j + 1])
//			{
//				Swap(&arr[j], &arr[j + 1]);
//			}
//		}
//	}
//	numberThreadsActive--;
//}