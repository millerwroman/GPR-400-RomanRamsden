#include "MinePool.h"

#include <iostream>
#include <string>


#include "Random.h"

MinePool* MinePool::msInstance{ nullptr };

MinePool* MinePool::GetSingleton()
{
	if (!msInstance) msInstance = new MinePool();

	return msInstance;
}

void MinePool::PrintResults()
{
	for (Mine* mine : mPool)
	{
		if(!mine) continue;
		std::cout << "Mine Object ID: " << std::to_string(mine->GetID())
			<< "\n Mine Targets: " << std::to_string(mine->GetNumTargets()) << "\n";
	}
	std::cout << "Total Mines: " << std::to_string(mMineCount) << "\n";
}

unsigned int MinePool::GetNumberOfMines()
{
	return mMineCount;
}

bool MinePool::IsValidIndex(unsigned ID)
{
	return ID < mMineCount;
}

Mine* MinePool::GetMineByID(unsigned ID)
{
	if (IsValidIndex(ID))
		return mPool[ID];
	else return nullptr;
}

void MinePool::DeleteMine(unsigned ID)
{
	if (!IsValidIndex(ID)) return;
	
	delete mPool[ID];
	mPool[ID] = mPool[mNumberObjects - 1];
	if(ID !=mNumberObjects-1)
	{
		mPool[ID]->SetID(ID);
		mPool[mNumberObjects - 1] = nullptr;
	}
	mNumberObjects--;
}

void MinePool::CreateMine(unsigned ID, unsigned team, float pos[3], float radius, bool active)
{
	if (mNumberObjects >= MAX_MINE_COUNT) return;

	if(radius==0.0f)
	{
		radius = GetRandomFloat32_Range(10.0f, 100.0f);
		mPool[mNumberObjects] = new Mine(ID, team, pos, radius, active);
	}
	else
	{
		mPool[mNumberObjects] = new Mine(ID, team, pos, radius, active);
	}
	mNumberObjects++;
}

void MinePool::PopulatePool(unsigned numTeams, unsigned minesPerTeam)
{
	for(unsigned int i=0; i<numTeams; ++i)
	{
		for(unsigned int j=0; j<minesPerTeam; ++j)
		{
			float pos[3];
			for(int a=0; a<3; ++a)
			{
				pos[a] = GetRandomFloat32_Range(-1000, 1000);
			}
			CreateMine(mNumberObjects, i, pos);
		}
	}
}
