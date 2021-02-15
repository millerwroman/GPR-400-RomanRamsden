#pragma once
#include <chrono>
#include <map>

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

class Timer
{
	std::map<std::string, TimerInstance*> instanceMap;

public:
	void StartTimer(std::string timerName)
	{
		TimerInstance* instance = new TimerInstance(timerName);
		instanceMap.insert(TimerPair(timerName, instance));
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

	~Timer()
	{
		for (auto pair : instanceMap)
		{
			delete pair.second;
			pair.second = nullptr;
		}
	}
};