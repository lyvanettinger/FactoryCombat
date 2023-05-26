
#include <string>

#include "../Header/Actor.h"
#include "../Header/Player.h"


Player::Player()
{
	mHealth = mMaxHealth;
	mAttack = 4;
}


void Player::AdjustCurrency(int pAdjustment)
{
	mCurrency += pAdjustment;

	// can't have negative currency
	if (mCurrency < 0)
	{
		mCurrency = 0;
	}
}

void Player::IncreaseAttack(int pIncrease)
{
	mAttack += pIncrease;
}

void Player::Heal(int pHealing)
{
	mHealth += pHealing;

	// can't exceed max health
	if (mHealth > mMaxHealth)
	{
		mHealth = mMaxHealth;
	}
}

int Player::GetHealth()
{
	return mHealth;
}


void Player::Reset()
{
	mHealth = mMaxHealth;
	mAttack = 4;
	mCurrency = 0;
}