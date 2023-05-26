#pragma once

// normal enemy
class QuatoEnemy : public Actor
{
public:
	QuatoEnemy()
	{
		mName = "Quato";
		mHealth = 6;
		mAttack = 2;
	};
};

// large enemy
class AttiEnemy : public Actor
{
public:
	AttiEnemy()
	{
		mName = "Atti";
		mHealth = 8;
		mAttack = 3;
	}
};

// heavy hitting squishy enemy
class FitoEnemy : public Actor
{
public:
	FitoEnemy()
	{
		mName = "Fito";
		mHealth = 4;
		mAttack = 5;
	}
};

// light hitting tanky enemy
class MetoEnemy : public Actor
{
public:
	MetoEnemy()
	{
		mName = "Meto";
		mHealth = 10;
		mAttack = 1;
	}
};