#pragma once
#include "Character.h"
#include "Types.h"
#include "Grid.h"
using namespace std;
class BattleField
{
public:

	BattleField();

	Grid* GridBattle;
	Types::GridBox* PlayerCurrentLocation;
	Types::GridBox* EnemyCurrentLocation;
	std::vector<Character*> AllPlayers; // Update list type to vector of ponters
	Character* PlayerCharacter; // Update type of variable to simple ponter
	Character* EnemyCharacter; // Update type of variable to simple ponter
	int CurrentTurn = 0;
	int NumberOfPossibleTiles = 0;
	int NumberOfXGrids = 8;
	int NumberOfYGrids = 10;

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


