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
    
    grid = new Grid(5, 5);
    AllPlayers = new list<Character>();
    int currentTurn = 0;
    int numberOfPossibleTiles = grid->grids.size();
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
    printf("Player Class Choice: {characterClass}");
    
    PlayerCharacter = std::make_shared<Character>(characterClass);
    
    PlayerCharacter->Health = 100;
    PlayerCharacter->BaseDamage = 20;
    PlayerCharacter->PlayerIndex = 0;

    CreateEnemyCharacter();

}

void BattleField::CreateEnemyCharacter()
{
    //randomly choose the enemy class and set up vital variables
    
    int randomInteger = GetRandomInt(1, 4);
    Types::CharacterClass enemyClass = (Types::CharacterClass)randomInteger;
    printf("Enemy Class Choice: {enemyClass}");
    EnemyCharacter = std::make_shared<Character>(enemyClass); // Updated the function to receive its correct value type
    EnemyCharacter->Health = 100;
    PlayerCharacter->BaseDamage = 20;
    PlayerCharacter->PlayerIndex = 1;
    StartGame();

}

void BattleField::StartGame()
{
    //populates the character variables and targets
    *EnemyCharacter->target = *PlayerCharacter; //Update reference type to received the other reference
    *PlayerCharacter->target = *EnemyCharacter; //Update reference type to received the other reference
    AllPlayers->push_back(*PlayerCharacter); //Update reference type to received the correct reference
    AllPlayers->push_back(*EnemyCharacter); //Update reference type to received the correct reference
    AlocatePlayers();
    StartTurn();

}

void BattleField::StartTurn() {

    if (currentTurn == 0)
    {
        //AllPlayers.Sort();  
    }
    std::list<Character>::iterator it;

    for (it = AllPlayers->begin(); it != AllPlayers->end(); ++it) {
        it->StartTurn(grid);
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
    
    int index = GetRandomInt(min, max);
    return index;
}

void BattleField::AlocatePlayers()
{
    AlocatePlayerCharacter();

}

void BattleField::AlocatePlayerCharacter()
{
    int random = 0;
    auto l_front = grid->grids.begin();
    advance(l_front, random);
    Types::GridBox* RandomLocation = &*l_front;

    if (!RandomLocation->ocupied)
    {
        //Types::GridBox* PlayerCurrentLocation = RandomLocation;
        PlayerCurrentLocation = &*l_front;
        l_front->ocupied = true;
        PlayerCharacter->currentBox = *l_front;
        AlocateEnemyCharacter();
    }
    else
    {
        AlocatePlayerCharacter();
    }
}

void BattleField::AlocateEnemyCharacter()
{
    
    int random = 24;
    auto l_front = grid->grids.begin();
    advance(l_front, random);
    Types::GridBox* RandomLocation = &*l_front;
    
    if (!RandomLocation->ocupied)
    {
        EnemyCurrentLocation = &*l_front;
        l_front->ocupied = true;
        EnemyCharacter->currentBox = *l_front;
        grid->drawBattlefield(5, 5);
    }
    else
    {
        AlocateEnemyCharacter();
    }
}