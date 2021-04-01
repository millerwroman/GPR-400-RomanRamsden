#pragma once

#include <iostream>
#include <process.h>
#include "Windows.h"

#include "PreformaceTimer.h"
#include "MinePool.h"
#include "Random.h"
#include "Mine.h"
//Play Setup
const unsigned int NUM_TEAMS = 5;
const unsigned int MINES_PER_TEAM = 500;
//Settings
const unsigned int RANDOM_SEED = 2435345;
const unsigned int MAX_THREADS = 16;

std::atomic_uint numThreadsActive;

void ThreadedFindTarget(void* wtfDoIDoWithThis)
{
	++numThreadsActive;

	MinePool* pool = MinePool::GetSingleton();
	bool working = true;
	while (working)
	{
		unsigned int index = pool->mTargetIndex;
		if (index < pool->GetNumberOfMines())
		{
			Mine* mine = pool->GetMineByID(index);
			mine->FindTargets();
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
	timer->StartTimer("BigBob");
	while (numThreadsActive > 0)
	{
		Sleep(1);
	}

	timer->StopTimer("BigBob");
	MinePool::GetSingleton()->PrintResults();
	std::cout << "Time Taken: " << std::to_string(timer->GetElapsedTime("BigBob")) << "\n";
	return 0;
}