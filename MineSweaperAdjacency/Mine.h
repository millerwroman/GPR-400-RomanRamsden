#pragma once
#include <vector>


class Mine
{
public:
	Mine() = delete;
	Mine(unsigned int objectID, unsigned int team, float position[3], float destructiveRad, bool active);
	~Mine();

	//Getters/Setters
	unsigned int GetNumTargets() { return mTargetIDList.size(); }
	float* GetPosition() const;
	unsigned int GetTeam() const;
	unsigned int GetID() const { return mMineID; }
	void SetID(unsigned int ID) { mMineID = ID; }

	//Static
	static float GetDistance(const float* posA, const float* posB);
	static float GetDistanceSqr(const float* posA, const float* posB);

	void FindTargets();
	//void Explode();
	//void TakeDamage(float damage);
private:
	unsigned int mMineID;
	float* mPosition;
	unsigned int mTeam;
	float mDestructRad;
	float mDestructRadSqr;
	float mExplosiveForce;
	bool mActive;

private:
	std::vector<unsigned int> mTargetIDList;

};
