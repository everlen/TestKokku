#include "Grid.h"
#include "BattleField.h"
#include <iostream>
#include <list>
#include <string>

using namespace std;

BattleField::BattleField() {
    
    GridBattle = new Grid(NumberOfXGrids, NumberOfYGrids);
    AllPlayers = {};
    PlayerCurrentLocation = nullptr; // initialized all variables in cronstruct like nullptr
    EnemyCurrentLocation = nullptr;
    PlayerCharacter = nullptr;
    EnemyCharacter = nullptr;
    int currentTurn = 0;
    int numberOfPossibleTiles = GridBattle->TotalGrids; //fix the incorrect assignment had invalid value chance
}

void BattleField::Setup()
{   
    GetPlayerChoice();
}

void BattleField::GetPlayerChoice()
{
    //asks for the player to choose between for possible classes via console.
    printf("Choose Between One of this Classes:\n");

    printf("[1] Paladin, [2] Warrior, [3] Cleric, [4] Archer\n");
    //store the player choice in a variable
    int choice;     
    cin >> choice; //Update input method
    
    if(choice > 0 && choice <= 4) //check if the selected number is a valid number 
    {
        CreatePlayerCharacter(choice);
        choice = -1;
    }
    else // remove switch 
    {
        choice = -1;
        printf("Invalid Value! Start game with default class:\n");
        CreatePlayerCharacter(1);
    }
}

void BattleField::CreatePlayerCharacter(int classIndex)
{
    Types::CharacterClass characterClass = (Types::CharacterClass)classIndex; //I remove the ponter on variable    
    PlayerCharacter = new Character(characterClass); // Update function to new variable type
    PlayerCharacter->Icon = 'P';
    PlayerCharacter->IsEnemy = false;
    PlayerCharacter->PlayerIndex = 0;
    
    printf("Player as 'P' | Class Choice: %s \n", PlayerCharacter->ClassName.c_str());

    CreateEnemyCharacter();
}

void BattleField::CreateEnemyCharacter()
{
    //randomly choose the enemy class and set up vital variables    
    int randomInteger = GetRandomInt(1, 4);
    Types::CharacterClass enemyClass = (Types::CharacterClass)randomInteger;
    
    EnemyCharacter = new Character(enemyClass); // Update function to new variable type
    EnemyCharacter->Icon = 'E';
    EnemyCharacter->IsEnemy = true;
    EnemyCharacter->PlayerIndex = 1;

    printf("Enemy as 'E' | Class Choice: %s \n", EnemyCharacter->ClassName.c_str()); //Update print location to received current infos of enemy
}

void BattleField::StartGame()
{
    //populates the character variables and targets
 
    EnemyCharacter->Target = PlayerCharacter; //Update reference type to right received the other ponter
    PlayerCharacter->Target = EnemyCharacter; //Update reference type to right received the other ponter
    AlocatePlayerCharacter(); // Alter call function to remove redundance function
    AlocateEnemyCharacter(); // Update call location to more control
    AllPlayers.insert(AllPlayers.begin(), PlayerCharacter); //Update reference type to received the correct reference 
    AllPlayers.insert(AllPlayers.begin(), EnemyCharacter); //Update reference type to received the correct reference
    //currentTurn = 0;
    HandleTurn(); //Start game with handle turn to more control
}

void BattleField::StartTurn() {

    printf("----TURN %i----\n", CurrentTurn+1);
    if (CurrentTurn == 0) // I make a sort start character function
    {
        int index =  GetRandomInt(0, 2);
        if(index != 0)
        {
            Character* Aux = AllPlayers[0];
            AllPlayers[0] = AllPlayers[1];
            AllPlayers[1] = Aux;
        }
    }

    for (int i = 0; i < AllPlayers.size(); i++) { //Simplified the for
        AllPlayers[i]->StartTurn(GridBattle);
    }
    GridBattle->drawBattlefield(GridBattle->XLength, GridBattle->YLength, PlayerCharacter->CurrentBox.Index, PlayerCharacter->Icon, EnemyCharacter->Icon); // Add draw function here to more control
    CurrentTurn++;
    HandleTurn();
}

void BattleField::HandleTurn()
{
    if(CurrentTurn>0)
    {
        if(PlayerCharacter->Health <= 0 && EnemyCharacter->Health <= 0)
        {
            printf("NO CONTEXT.\n");
            system("pause");
            return;
        }
        else if (PlayerCharacter->Health <= 0)
        {
            printf("YOU LOSE!\n");
            system("pause");
            return;
        }
        else if (EnemyCharacter->Health <= 0)
        {
            printf("YOU WIN!\n");
            system("pause");
            return;
        }
        else
        {
            printf("\n");
            printf("Send 'P' to start the next turn...\n"); //Update method to pass turn
            printf("\n");
            while(cin.get() != 'p');
            
            StartTurn();
        }
    }
    else
    {
        GridBattle->drawBattlefield(GridBattle->XLength, GridBattle->YLength, PlayerCharacter->CurrentBox.Index, PlayerCharacter->Icon, EnemyCharacter->Icon); // Add draw function here to more control
        printf("\n");
        printf("Send 'P' to start game...\n"); //Update method to pass turn
        printf("\n");
        while(cin.get() != 'p');
        
        StartTurn();
    }
}

int BattleField::GetRandomInt(int min, int max)
{    
    int index = std::rand() % max+min; //Fix the infinity loop
    return index;
}

void BattleField::AlocatePlayerCharacter()
{
    int Random = GetRandomInt(0, GridBattle->TotalGrids-1); //Update to random number get value of dynamic grids numbers
    Types::GridBox* RandomLocation = &GridBattle->grids[Random]; //I simplified the method to get RandomLocation

    if (!RandomLocation->Ocupied)
    {
        //Types::GridBox* PlayerCurrentLocation = RandomLocation;
        PlayerCurrentLocation = RandomLocation;
        RandomLocation->Ocupied = true;
        PlayerCharacter->CurrentBox = *RandomLocation;
    }
    else
    {
        AlocatePlayerCharacter();
    }
}

void BattleField::AlocateEnemyCharacter()
{
    
    int Random = GetRandomInt(0, GridBattle->TotalGrids-1); //Update to random number get value of dynamic grids numbers
    Types::GridBox* RandomLocation = &GridBattle->grids[Random]; //I simplified the method to get RandomLocation
    
    if (!RandomLocation->Ocupied)
    {
        EnemyCurrentLocation = RandomLocation;
        RandomLocation->Ocupied = true;
        EnemyCharacter->CurrentBox = *RandomLocation;
    }
    else
    {
        AlocateEnemyCharacter();
    }
}