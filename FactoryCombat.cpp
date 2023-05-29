
/// trying to uphold a consistent naming convention:
// * camelCase for variables, with prefixes:
// m = member
// p = pointer
// g = global
// p = function parameter
// * UpperCamelCase for functions and class names
// * no _


#include <iostream>
#include <cstdlib>

#include "Header/Actor.h"
#include "Header/Player.h"
#include "Header/Enemies.h"
#include "Header/EnemyFactory.h"

using namespace std;

int GetRandomNum(int pMin, int pMax)
{
	return pMin + (rand() % pMax + 1);
}


int main()
{
	// seed rand
	srand((unsigned)time(NULL));

	// initialize game variables
	EnemyFactory* pEnemyFactory = new EnemyFactory;
	Player* pPlayer = new Player();
	Actor* pCurrentEnemy = pEnemyFactory->CreateEnemy(GetRandomNum(0, 3));
	string input = " ";
	bool inputIsNotValid = true;

	// start game text
	cout << "Welcome to FactoryCombat! This is a small,\n";
	cout << "simple, fast paced action game. Enjoy!\n\n";
	cin.get();

	// get player name
	string playerName;
	cout << "Dear traveller, what is your name? ";
	cin >> playerName;
	cout << "\nWonderful! Let us begin, " + playerName + "!\n\n";
	cin.get();

	// first enemy text
	cout << "An enemy approaches...";
	cin.get();
	cout << "It's a " + pCurrentEnemy->GetName() + "!";
	cin.get();

	// main game loop
	while (pPlayer->mIsAlive)
	{
		// player actions options text
		cout << "It looks hostile.. What will you do?\n";
		cout << "1 Attack\n";
		cout << "2 Run away\n";
		cout << "3 Do nothing\n";

		// player action choice texts and executions
		inputIsNotValid = true;
		while (inputIsNotValid)
		{
			cin >> input;
			// ATTACK
			if (input == "1")
			{
				inputIsNotValid = false;

				// player attacks
				pCurrentEnemy->TakeDamage(pPlayer->Attack());
				cout << playerName + " did " + to_string(pPlayer->Attack())
					+ " damage to " + pCurrentEnemy->GetName() + "!\n";

				// check if enemy died
				if (!pCurrentEnemy->mIsAlive)
				{
					cout << pCurrentEnemy->GetName() + " has been defeated!\n";
				}
				else
				{
					// enemy attacks
					pPlayer->TakeDamage(pCurrentEnemy->Attack());
					cout << pCurrentEnemy->GetName() + " did "
						+ to_string(pCurrentEnemy->Attack()) + " damage to "
						+ playerName + "!\n";
					// player status
					cout << playerName + " has " + to_string(pPlayer->GetHealth())
						+ "HP left!\n";
				}
				cin.get();
			}
			// RUN AWAY
			else if (input == "2") 
			{
				inputIsNotValid = false;

				// (try to) run away
				cout << playerName + " tries to run away.. ";
				cin.get();
				// 2 : 1 chance of succeeding/not succeeding to run away
				switch (GetRandomNum(0, 2))
				{
				case 0:
				case 1: // runs away
					cout << "their attempt was succesful!";
					pCurrentEnemy->mIsAlive = false;
					break;

				case 2: // can't escape
					cout << "their attempt was not succesful!\n";
					// enemy attacks
					pPlayer->TakeDamage(pCurrentEnemy->Attack());
					cout << pCurrentEnemy->GetName() + " did "
						+ to_string(pCurrentEnemy->Attack()) + " damage to "
						+ playerName + "!\n";
					// player status
					cout << playerName + " has " + to_string(pPlayer->GetHealth())
						+ "HP left!\n";
				}
				cin.get();
			}
			// DO NOTHING
			else if (input == "3")
			{
				inputIsNotValid = false;

				// enemy attacks
				pPlayer->TakeDamage(pCurrentEnemy->Attack());
				cout << pCurrentEnemy->GetName() + " did "
					+ to_string(pCurrentEnemy->Attack()) + " damage to "
					+ playerName + "!";
				cin.get();
				// player status
				cout << playerName + " has " + to_string(pPlayer->GetHealth())
					+ "HP left!\n";
				cin.get();
			}
		}

		// spawn new enemy if it died
		if (!pCurrentEnemy->mIsAlive)
		{
			// cleanup and spawn new enemy
			delete pCurrentEnemy;
			pCurrentEnemy = pEnemyFactory->CreateEnemy(GetRandomNum(0, 3));

			// respawn text
			cout << "A new enemy approaches...";
			cin.get();
			cout << "It's a " + pCurrentEnemy->GetName() + "!";
		}


		cin.get();
		// if player dies
		if (!pPlayer->mIsAlive)
		{
			cout << "Oh god! You look beaten up, " + playerName + "...\n";
			// give player a chance to start over
			cout << "Would you like to try again? Y/N ";
			while (inputIsNotValid)
			{
				cin >> input;
				// check if input is valid
				if (input == "Y" && input == "y")
				{
					inputIsNotValid = false;

					// reset player
					cout << "\nGreat! Here we go again..\n\n";
					pPlayer->Reset();

					// cleanup current and spawn new enemy
					delete pCurrentEnemy;
					pCurrentEnemy = pEnemyFactory->CreateEnemy(GetRandomNum(0, 3));
					// first enemy text
					cout << "An enemy approaches...";
					cin.get();
					cout << "It's a " + pCurrentEnemy->GetName() + "!";
					cin.get();
				}
				else if (input == "N" && input == "n")
				{
					inputIsNotValid = false;
				}
			}
		}
	}

	// cleanup and end game text
	delete pPlayer;
	cout << "\n\n\nThank you for playing " + playerName + "!";

	cin.get();

	return 0;
}