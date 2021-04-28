#pragma once

#include <iostream>
#include <process.h>
#include "Windows.h"

#include "PreformaceTimer.h"
#include "MinePool.h"
#include "Random.h"
#include "Mine.h"

class TestingThread;
//Play Setup
const unsigned int NUM_TEAMS = 5;
const unsigned int MINES_PER_TEAM = 500;
//Settings
const unsigned int RANDOM_SEED = 2435345;
const unsigned int MAX_THREADS = 16;

std::vector<TestingThread*> threads;
std::atomic_uint numThreadsActive = 0;
std::atomic_uint numThreadsStarted = 0;

void ThreadedFindTarget(void* wtfDoIDoWithThis)
{
	++numThreadsActive;
	++numThreadsStarted;

	MinePool* pool = MinePool::GetSingleton();
	bool working = true;
	while (working)
	{
		unsigned int index = pool->mTargetIndex;
		if (index < pool->GetNumberOfMines())
		{
			Mine* mine = pool->GetMineByID(index);
			if (mine)
			{
				mine->FindTargets();
			}
		}
		else
		{
			working = false;
		}
		
	}

	--numThreadsActive;
}
void StandardFindTarget()
{
	MinePool* pool = MinePool::GetSingleton();

	for(int i=0; i<pool->GetNumberOfMines(); ++i)
	{
		Mine* mine = pool->GetMineByID(i);
		if (mine)
		{
			mine->FindTargets();
		}
		
	}
}

class TestingThread
{
public:
	TestingThread() = default;
	~TestingThread() = default;

	static void FindTargets()
	{
		_beginthread(ThreadedFindTarget, 0, nullptr);
	}
};


int main()
{
	SetSeed(RANDOM_SEED);
	Timer* timer = new Timer();
	TestingThread* Tester = new TestingThread();
	//Inital Pool Setup
	MinePool::GetSingleton()->PopulatePool(NUM_TEAMS, MINES_PER_TEAM);
	for (int i = 0; i < MAX_THREADS; ++i)
	{
		threads.push_back(new TestingThread());
	}


	
	timer->StartTimer("Time");
	//For Threaded Finding----------------
	numThreadsStarted = 0;

	for(int i=0; i<MAX_THREADS; ++i)
	{
		threads[i]->FindTargets();
	}
	do
	{
		Sleep(1);
	} while (numThreadsActive > 0);

	
	//StandardFindTarget();
	

	timer->StopTimer("Time");
	MinePool::GetSingleton()->PrintResults();
	std::cout << "Time Taken: " << std::to_string(timer->GetElapsedTime("Time")) << "\n";
	return 0;
}