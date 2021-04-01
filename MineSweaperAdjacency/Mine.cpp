#pragma once

#include "Mine.h"
#include "MinePool.h"
#include <cmath>

Mine::Mine(unsigned objectID, unsigned team, float position[3], float destructiveRad, bool active)
{
	mMineID = objectID;
	mTeam = team;
	position = position;
	mDestructRad = destructiveRad;
	mDestructRadSqr = mDestructRad * mDestructRad;
	mActive = active;
}

Mine::~Mine()
{
	//Explode();
	delete mPosition;
	mPosition = nullptr;
}

float* Mine::GetPosition() const
{
	return mPosition;
}

unsigned int Mine::GetTeam() const
{
	return mTeam;
}

float Mine::GetDistance(const float* posA, const float* posB)
{
	return std::sqrt(GetDistanceSqr(posA, posB));
}

float Mine::GetDistanceSqr(const float* posA, const float* posB)
{
	float disSqr = 0;
	for (int i = 0; i < 3; ++i)
	{
		const float disVec = posA[i] - posB[i];
		disSqr = disVec * disVec;
	}
	return disSqr;
}

void Mine::FindTargets()
{
	if (!mActive) return;

	mTargetIDList.clear();
	MinePool* pool = MinePool::GetSingleton();
	for (unsigned int i = 0; i < pool->GetNumberOfMines(); ++i)
	{
		if (i == mMineID) continue;;

		Mine* mine = pool->GetMineByID(i);
		float dis = GetDistanceSqr(mPosition, mine->GetPosition());

		if (dis > mDestructRadSqr) continue;
		mTargetIDList.push_back(mine->GetID());
	}
}

//void Mine::Explode()
//{
//}
//
//void Mine::TakeDamage(float damage)
//{
//}