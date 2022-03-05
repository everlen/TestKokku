#pragma once
#include "Character.h"
#include "Types.h"
#include <list>
#include <iostream>
#include "Grid.h"
using namespace std;
class BattleField
{
public:

	BattleField();

	Grid* grid;
	Types::GridBox* PlayerCurrentLocation;
	Types::GridBox* EnemyCurrentLocation;
	std::vector<Character*> AllPlayers; // Update list type to vector of ponters
	Character* PlayerCharacter; // Update type of variable to simple ponter
	Character* EnemyCharacter; // Update type of variable to simple ponter
	int currentTurn = 0;
	int numberOfPossibleTiles = 0;
	int numberOfXGrids = 8;
	int numberOfYGrids = 20;

	void Setup();

	void GetPlayerChoice();

	void CreatePlayerCharacter(int classIndex);

	void CreateEnemyCharacter();

	void StartGame();

	void StartTurn();

	void HandleTurn();

	int GetRandomInt(int min, int max);

	void AlocatePlayerCharacter();

	void AlocateEnemyCharacter();
};


