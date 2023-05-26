#pragma once


class Player : public Actor
{
public:
	Player();

	void AdjustCurrency(int pAdjustment);
	void IncreaseAttack(int pIncrease);
	void Heal(int pHealing);

	int GetHealth();

	void Reset();

private:
	// private variables
	int mCurrency = 0;
	int mMaxHealth = 15;
};