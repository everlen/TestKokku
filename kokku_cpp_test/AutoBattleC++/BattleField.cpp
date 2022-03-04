#include "Grid.h"
#include "BattleField.h"
#include "Types.h"
#include "Character.h"
#include <iostream>
#include "BattleField.h"
#include <list>
#include <string>

using namespace std;

BattleField::BattleField() {
    
    grid = new Grid(numberOfXGrids, numberOfYGrids);
    AllPlayers = new list<Character*>();
    int currentTurn = 0;
    int numberOfPossibleTiles = grid->TotalGrids; //fix the incorrect assignment had invalid value chance
    Setup();
}

void BattleField::Setup()
{   
    GetPlayerChoice();
}

void BattleField::GetPlayerChoice()
{
    //asks for the player to choose between for possible classes via console.
    printf("Choose Between One of this Classes:\n");

    printf("[1] Paladin, [2] Warrior, [3] Cleric, [4] Archer");
    //store the player choice in a variable
    std::string choice;

    std::getline(std::cin, choice);
    
    cin >> choice;
    int choiceNumber = stoi(choice); //I converted the received input to an integer value 
    if(choiceNumber <= 0 || choiceNumber > 4) //check if the selected number is a valid number 
    {
        choiceNumber = -1;
        printf("Invalid Value!:\n");
    }
    switch (choiceNumber)
    {
    case 1:
        CreatePlayerCharacter(choiceNumber);
        break;
    case 2:
        CreatePlayerCharacter(choiceNumber);
        break;
    case 3:
        CreatePlayerCharacter(choiceNumber);
        break;
    case 4:
        CreatePlayerCharacter(choiceNumber);
        break;
    default:
        GetPlayerChoice();
        break;
    }
}

void BattleField::CreatePlayerCharacter(int classIndex)
{
    Types::CharacterClass characterClass = (Types::CharacterClass)classIndex; //I remove the ponter on variable    
    PlayerCharacter = new Character(characterClass); // Update function to new variable type
    
    PlayerCharacter->Health = 100;
    PlayerCharacter->BaseDamage = 20;
    PlayerCharacter->PlayerIndex = 0;
    
    printf("Player Class Choice: %s \n", PlayerCharacter->ClassName.c_str());

    CreateEnemyCharacter();
}

void BattleField::CreateEnemyCharacter()
{
    //randomly choose the enemy class and set up vital variables    
    int randomInteger = GetRandomInt(1, 4);
    Types::CharacterClass enemyClass = (Types::CharacterClass)randomInteger;
    
    EnemyCharacter = new Character(enemyClass); // Update function to new variable type
    EnemyCharacter->Health = 100;
    PlayerCharacter->BaseDamage = 20;
    PlayerCharacter->PlayerIndex = 1;

    printf("Enemy Class Choice: %s \n", EnemyCharacter->ClassName.c_str()); //Update print location to received current infos of enemy
    
    StartGame();
}

void BattleField::StartGame()
{
    //populates the character variables and targets
    *EnemyCharacter->target = *PlayerCharacter; //Update reference type to received the other reference
    *PlayerCharacter->target = *EnemyCharacter; //Update reference type to received the other reference
    AllPlayers->push_back(PlayerCharacter); //Update reference type to received the correct reference
    AllPlayers->push_back(EnemyCharacter); //Update reference type to received the correct reference
    AlocatePlayerCharacter(); // Alter call function to remove redundance function
    StartTurn();

}

void BattleField::StartTurn() {

    if (currentTurn == 0)
    {
        //AllPlayers.Sort();  
    }
    
    for (int i = 0; i < AllPlayers->size(); i++) { //Simplified the for
        AllPlayers[i].get()->StartTurn(grid);
    }

    currentTurn++;
    HandleTurn();
}

void BattleField::HandleTurn()
{ 
    if (PlayerCharacter->Health == 0)
    {
        return;
    }
    else if (EnemyCharacter->Health == 0)
    {
        printf("\n");

        // endgame?

        printf("\n");

        return;
    }
    else
    {
        printf("\n");
        printf("Click on any key to start the next turn...\n");
        printf("\n");

        //TODO
        //ConsoleKeyInfo key = Console.ReadKey();
        StartTurn();
    }
}

int BattleField::GetRandomInt(int min, int max)
{
    
    int index = min + rand() % max; //Fix the infinity loop
    return index;
}

void BattleField::AlocatePlayerCharacter()
{
    int Random = GetRandomInt(0, grid->TotalGrids-1); //Update to random number get value of dynamic grids numbers
    Types::GridBox* RandomLocation = &grid->grids[Random]; //I simplified the method to get RandomLocation

    if (!RandomLocation->ocupied)
    {
        //Types::GridBox* PlayerCurrentLocation = RandomLocation;
        PlayerCurrentLocation = RandomLocation;
        RandomLocation->ocupied = true;
        PlayerCharacter->currentBox = *RandomLocation;
        AlocateEnemyCharacter();
    }
    else
    {
        AlocatePlayerCharacter();
    }
}

void BattleField::AlocateEnemyCharacter()
{
    
    int Random = GetRandomInt(0, grid->TotalGrids-1); //Update to random number get value of dynamic grids numbers
    Types::GridBox* RandomLocation = &grid->grids[Random]; //I simplified the method to get RandomLocation
    
    if (!RandomLocation->ocupied)
    {
        EnemyCurrentLocation = RandomLocation;
        RandomLocation->ocupied = true;
        EnemyCharacter->currentBox = *RandomLocation;
        grid->drawBattlefield(numberOfXGrids, numberOfYGrids);
    }
    else
    {
        AlocateEnemyCharacter();
    }
}