#include <atomic>
#include <process.h>
#include "PreformaceTimer.h"

struct BubbleArr
{
	int* arr;
	int size;
};

void Swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

static unsigned int numberThreadsActive = 0;
static unsigned int numberThreadsStarted = 0;
std::atomic_int currentCount(0);
std::atomic_int totalRuns(0);
static InstanceInfo info[10000];
static BubbleArr bubbleInfo[10000];

void ThreadedBubbleTest(void* useless)
{
	numberThreadsActive++;
	START:
	info[currentCount].StartTime = Timer::GetTime();

	for (int i = 0; i < bubbleInfo[currentCount].size - 1; ++i)
	{
		for (int j = 0; j < bubbleInfo[currentCount].size - i - 1; ++j)
		{
			if (bubbleInfo[currentCount].arr[j] > bubbleInfo[currentCount].arr[j + 1])
			{
				Swap(&bubbleInfo[currentCount].arr[j], &bubbleInfo[currentCount].arr[j + 1]);
			}
		}
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

	static void ThreadedBubble()
	{
		int bob;
		_beginthread(ThreadedBubbleTest, 0, nullptr);
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