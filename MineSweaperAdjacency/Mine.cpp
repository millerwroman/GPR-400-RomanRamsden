#pragma once

#include "Mine.h"
#include "MinePool.h"
#include <cmath>

#include "Random.h"

Mine::Mine(unsigned objectID, unsigned team, float destructiveRad, bool active)
{
	mMineID = objectID;
	mTeam = team;
	mDestructRad = destructiveRad;
	mDestructRadSqr = mDestructRad * mDestructRad;
	mActive = active;

	for (int a = 0; a < 3; ++a)
	{
		mPosition[a] = GetRandomFloat32_Range(0, 1000);
	}
}

Mine::~Mine()
{
	//Explode();
}

float* Mine::GetPosition()
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