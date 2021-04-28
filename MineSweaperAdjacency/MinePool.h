#pragma once
#include "Mine.h"
#include <atomic>

const int MAX_MINE_COUNT = 100000; //100,000

class MinePool
{
public:
	//Singleton Stuff
	MinePool(MinePool& other) = delete;
	void operator = (const MinePool&) = delete;
	static MinePool* GetSingleton();
	void PrintResults();

public:
	unsigned int GetNumberOfMines();
	Mine* GetMineByID(unsigned int ID);
	void DeleteMine(unsigned int ID);
	void CreateMine(unsigned int ID, unsigned int team, float radius=0, bool active = true);
	void PopulatePool(unsigned int numTeams, unsigned int minesPerTeam);
	

	void ResetFindTargetIndex() { mTargetIndex = 0; };
	std::atomic_uint mTargetIndex;
private:
	static MinePool* msInstance;
	bool IsValidIndex(unsigned int ID);
	unsigned int mNumberObjects;
	Mine* mPool[MAX_MINE_COUNT];
	//unsigned int mMineCount;
	MinePool() = default;
	~MinePool() = default;
};


