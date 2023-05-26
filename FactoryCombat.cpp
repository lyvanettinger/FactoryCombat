
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
	EnemyFactory* gpEnemyFactory = new EnemyFactory;
	Player* gpPlayer = new Player();
	Actor* gpCurrentEnemy = gpEnemyFactory->CreateEnemy(GetRandomNum(0, 3));
	string gInput = " ";
	bool gInputIsNotValid = true;

	// start game text
	cout << "Welcome to FactoryCombat! This is a small,\n";
	cout << "simple, fast paced action game. Enjoy!\n\n";
	cin.get();

	// get player name
	string gPlayerName;
	cout << "Dear traveller, what is your name? ";
	cin >> gPlayerName;
	cout << "\nWonderful! Let us begin, " + gPlayerName + "!\n\n";
	cin.get();

	// first enemy text
	cout << "An enemy approaches...";
	cin.get();
	cout << "It's a " + gpCurrentEnemy->GetName() + "!";
	cin.get();

	// main game loop
	while (gpPlayer->mIsAlive)
	{
		// player actions options text
		cout << "It looks hostile.. What will you do?\n";
		cout << "1 Attack\n";
		cout << "2 Run away\n";
		cout << "3 Do nothing\n";

		// player action choice texts and executions
		gInputIsNotValid = true;
		while (gInputIsNotValid)
		{
			cin >> gInput;
			// ATTACK
			if (gInput == "1")
			{
				gInputIsNotValid = false;

				// player attacks
				gpCurrentEnemy->TakeDamage(gpPlayer->Attack());
				cout << gPlayerName + " did " + to_string(gpPlayer->Attack())
					+ " damage to " + gpCurrentEnemy->GetName() + "!\n";

				// check if enemy died
				if (!gpCurrentEnemy->mIsAlive)
				{
					cout << gpCurrentEnemy->GetName() + " has been defeated!\n";
				}
				else
				{
					// enemy attacks
					gpPlayer->TakeDamage(gpCurrentEnemy->Attack());
					cout << gpCurrentEnemy->GetName() + " did "
						+ to_string(gpCurrentEnemy->Attack()) + " damage to "
						+ gPlayerName + "!\n";
					// player status
					cout << gPlayerName + " has " + to_string(gpPlayer->GetHealth())
						+ "HP left!\n";
				}
				cin.get();
			}
			// RUN AWAY
			else if (gInput == "2") 
			{
				gInputIsNotValid = false;

				// (try to) run away
				cout << gPlayerName + " tries to run away.. ";
				cin.get();
				// 2 : 1 chance of succeeding/not succeeding to run away
				switch (GetRandomNum(0, 2))
				{
				case 0:
				case 1: // runs away
					cout << "their attempt was succesful!";
					gpCurrentEnemy->mIsAlive = false;
					break;

				case 2: // can't escape
					cout << "their attempt was not succesful!\n";
					// enemy attacks
					gpPlayer->TakeDamage(gpCurrentEnemy->Attack());
					cout << gpCurrentEnemy->GetName() + " did "
						+ to_string(gpCurrentEnemy->Attack()) + " damage to "
						+ gPlayerName + "!\n";
					// player status
					cout << gPlayerName + " has " + to_string(gpPlayer->GetHealth())
						+ "HP left!\n";
				}
				cin.get();
			}
			// DO NOTHING
			else if (gInput == "3")
			{
				gInputIsNotValid = false;

				// enemy attacks
				gpPlayer->TakeDamage(gpCurrentEnemy->Attack());
				cout << gpCurrentEnemy->GetName() + " did "
					+ to_string(gpCurrentEnemy->Attack()) + " damage to "
					+ gPlayerName + "!";
				cin.get();
				// player status
				cout << gPlayerName + " has " + to_string(gpPlayer->GetHealth())
					+ "HP left!\n";
				cin.get();
			}
		}

		// spawn new enemy if it died
		if (!gpCurrentEnemy->mIsAlive)
		{
			// cleanup and spawn new enemy
			delete gpCurrentEnemy;
			gpCurrentEnemy = gpEnemyFactory->CreateEnemy(GetRandomNum(0, 3));

			// respawn text
			cout << "A new enemy approaches...";
			cin.get();
			cout << "It's a " + gpCurrentEnemy->GetName() + "!";
		}


		cin.get();
		// if player dies
		if (!gpPlayer->mIsAlive)
		{
			cout << "Oh god! You look beaten up, " + gPlayerName + "...\n";
			// give player a chance to start over
			cout << "Would you like to try again? Y/N ";
			while (gInputIsNotValid)
			{
				cin >> gInput;
				// check if input is valid
				if (gInput == "Y" && gInput == "y")
				{
					gInputIsNotValid = false;

					// reset player
					cout << "\nGreat! Here we go again..\n\n";
					gpPlayer->Reset();

					// cleanup current and spawn new enemy
					delete gpCurrentEnemy;
					gpCurrentEnemy = gpEnemyFactory->CreateEnemy(GetRandomNum(0, 3));
					// first enemy text
					cout << "An enemy approaches...";
					cin.get();
					cout << "It's a " + gpCurrentEnemy->GetName() + "!";
					cin.get();
				}
				else if (gInput == "N" && gInput == "n")
				{
					gInputIsNotValid = false;
				}
			}
		}
	}

	// cleanup and end game text
	delete gpPlayer;
	cout << "\n\n\nThank you for playing " + gPlayerName + "!";

	cin.get();

	return 0;
}