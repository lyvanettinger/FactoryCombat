#pragma once

#include <string>

// base class for player and all enemies
class Actor
{
public:
	Actor() { };
	// basic actions
	int Attack();
	virtual void TakeDamage(int pDamage);

	std::string GetName();

	// basic stats
	bool mIsAlive = true;
protected:
	std::string mName = "base";
	int mHealth = 0;
	int mAttack = 0;

};