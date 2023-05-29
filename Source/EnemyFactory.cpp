
#include "../Header/Actor.h"
#include "../Header/Enemies.h"
#include "../Header/EnemyFactory.h"

Actor* EnemyFactory::CreateEnemy(int pIndex)
{
	switch (pIndex)
	{
	case 0:
		return new QuatoEnemy();
	case 1:
		return new AttiEnemy();
	case 2:
		return new FitoEnemy();
	case 3:
		return new MetoEnemy();
	default:
		return new QuatoEnemy();
	}
}