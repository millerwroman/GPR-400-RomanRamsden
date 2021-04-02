#pragma once
#include <iostream>
#include <ostream>
#include <Windows.h>
#include "Random.h"
#include "WorkerThread.h"


void PopulateArray(BubbleArr& bubble, int sizeToPopulate)
{
	for (int i = 0; i < sizeToPopulate; ++i)
	{
		bubble.arr[i] = static_cast<int>(GetRandomFloat32_Range(0, (sizeToPopulate)));
	}
	bubble.size = sizeToPopulate;
}

void TestBubbleThreaded(int runTimes, RunInfo& info)
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
		threadList[i]->ThreadedBubble();
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