#ifndef PERFORMANCE_TIMER_H
#define PERFORMANCE_TIMER_H

#include <chrono>
#include <functional>
#include <map>
#include <atomic>
#include <string>

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::steady_clock::time_point Time;
typedef std::chrono::duration<float> ElapsedTime_f;

class TimerInstance
{
	std::string name;
	Time startTime;
	Time endTime;
	ElapsedTime_f elapsedTime;
public:
	std::string GetName() { return name; }
	Time GetStartTime() const { return startTime; }
	Time GetEndTime() const { return endTime; }

	void Start() { startTime = Clock::now(); }
	void Stop() { endTime = Clock::now(); elapsedTime = endTime - startTime; }
	float GetElapsedTime() const { return elapsedTime.count(); }

	TimerInstance(std::string name_new)
	{
		name = name_new;
		startTime = Clock::now();
	}
};

typedef std::pair<std::string, TimerInstance*> TimerPair;
typedef std::map<std::string, TimerInstance*>::iterator Iterator;

struct RunInfo
{
	float minTime = 99999;
	float maxTime = 0;
	float averageTime = 0;
};

struct RunInfoAtomic
{
	std::atomic_ulong minTime = 99999;
	std::atomic_ulong maxTime = 0;
	std::atomic_ulong averageTime = 0;
};

struct InstanceInfo
{
	Time StartTime;
	Time EndTime;
};


class Timer
{
	std::map<std::string, TimerInstance*> instanceMap;

public:

	/*RunInfo RunSetTimes(int runCount, const std::function<void()>& func, const std::function<void()>& setup)
	{
		RunInfo info = RunInfo();
		info.runQuantity = runCount;
		for (int i = 0; i < runCount; ++i)
		{
			setup();
			StartTimer("RunSetTime");
			func();
			float timeTaken = StopTimer("RunSetTime");

			info.averageTime += timeTaken;
			info.minTime = (timeTaken < info.minTime ? timeTaken : info.minTime);
			info.maxTime = (timeTaken > info.maxTime ? timeTaken : info.maxTime);
		}

		info.averageTime /= runCount;
		return info;
	}*/

	void StartTimer(std::string timerName)
	{
		const Iterator item = instanceMap.find(timerName);
		if (item != instanceMap.end())
		{
			delete item->second;
			item->second = nullptr;
			item->second = new TimerInstance(timerName);
		}
		else
		{
			TimerInstance* instance = new TimerInstance(timerName);
			instanceMap.insert(TimerPair(timerName, instance));
		}
	}

	float StopTimer(std::string timerName)
	{
		const Iterator item = instanceMap.find(timerName);

		if (item == instanceMap.end()) return 0.0f;

		TimerInstance* instance = item->second;
		instance->Stop();
		return instance->GetElapsedTime();
	}

	float GetElapsedTime(std::string timerName)
	{
		TimerInstance* instance = instanceMap.find(timerName)->second;
		return instance->GetElapsedTime();
	}

	static float GetElapsedTime(InstanceInfo& info)
	{
		return (info.EndTime - info.StartTime).count();
	}

	static Time GetTime()
	{
		return Clock::now();
	}

	static RunInfo ProcessInstanceArray(InstanceInfo* arr, int size)
	{
		RunInfo info;
		unsigned long long averageTime = 0;
		for(int i=0;i<size; ++i)
		{
			float timeTaken = GetElapsedTime(arr[i]);
			averageTime += timeTaken;
			info.minTime = (timeTaken < info.minTime ? timeTaken : info.minTime);
			info.maxTime = (timeTaken > info.maxTime ? timeTaken : info.maxTime);
		}

		return info;
	}

	static void PrintInfo(const RunInfo& info)
	{
		std::string out = "RunInfo: \nMin Time: " + std::to_string(info.minTime) + "\nMax Time: " + std::to_string(info.maxTime)
			+ "\n Average Time: " + std::to_string(info.averageTime) + "\n\n\n\n";
		std::cout << out;
	}

	~Timer()
	{
		for (auto pair : instanceMap)
		{
			delete pair.second;
			pair.second = nullptr;
		}
	}
};

#endif
