
#include "../Header/Actor.h"


int Actor::Attack()
{
	return mAttack;
}

void Actor::TakeDamage(int pDamage)
{
	mHealth -= pDamage;

	// check if it died
	if (mHealth < 0)
	{
		mIsAlive = false;
	}
}

std::string Actor::GetName()
{
	return mName;
}