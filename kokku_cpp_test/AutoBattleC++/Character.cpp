#include "Character.h" //I cleaned out the redundant includes and kept them only in the header file
#include <vector>
#include <algorithm>

Character::Character(Types::CharacterClass characterClass)
{
    //Set a base value in variables on class
    Health = 100;
    BaseDamage = 20;
    PlayerIndex = 0;
    DamageMultiplier = 1.0f;
    IsDead = false;
    Icon = 'X';
    string ClassNames[] = {"Paladin", "Warrior", "Cleric", "Archer"}; //Add vector of class names
    ClassName = ClassNames[characterClass -1]; //Set name Class in character constructor
    currentBox = *new Types::GridBox(); //Fix constructor adding a initialization in this variable
    target = this; //Fix warning not initializate
}

Character::~Character() 
{

}

bool Character::TakeDamage(float amount) 
{
	if ((Health -= BaseDamage) <= 0) 
	{
		Die();
		return true;
	}
	return false;
}

void Character::Die() 
{
	// TODO >> kill
	//TODO >> end the game?
}

void Character::WalkTo(bool canWalk) 
{

}



void Character::StartTurn(Grid* battlefield)
{
    if (CheckCloseTargets(battlefield))
    {
        Attack(Character::target);

        if(IsEnemy)
            printf("Enemy %s attack the player %s \n", ClassName.c_str(), target->ClassName.c_str());
        else
            printf("Player %s attack the enemy %s \n", ClassName.c_str(), target->ClassName.c_str());
    }
    else
    {   // if there is no target close enough, calculates in wich direction this character should move to be closer to a possible target
        if (currentBox.xIndex > target->currentBox.xIndex + 1) //Verify if character is in side grid
        {
            if(currentBox.index > 0) // Fix incorrect use to "!="            
            {
                currentBox.ocupied = false;
                battlefield->grids[currentBox.index] = currentBox;

                currentBox = battlefield->grids[currentBox.index - 1];
                currentBox.ocupied = true;
                battlefield->grids[currentBox.index] = currentBox;
                
                if(IsEnemy)
                    printf("\nEnemy %s walked left \n", ClassName.c_str());  //Console.WriteLine($"Player {PlayerIndex} walked left\n");
                else
                    printf("\nPlayer %s walked left \n", ClassName.c_str());  //Console.WriteLine($"Player {PlayerIndex} walked left\n");
            }
            else
            {
                printf("Current index invalid");
            }                
        }
        else if (currentBox.xIndex < target->currentBox.xIndex - 1)
        {
            if(currentBox.index < battlefield->TotalGrids - 1)
            {
                currentBox.ocupied = false;
                battlefield->grids[currentBox.index] = currentBox;
                
                currentBox = battlefield->grids[currentBox.index + 1];
                currentBox.ocupied = true;
                battlefield->grids[currentBox.index] = currentBox;
                
                if(IsEnemy)
                    printf("\nEnemy %s walked right \n", ClassName.c_str());  //Console.WriteLine($"Player {PlayerIndex} walked left\n");
                else
                    printf("\nPlayer %s walked right \n", ClassName.c_str());  //Console.WriteLine($"Player {PlayerIndex} walked left\n");
            }
            else
            {
                printf("Current index invalid");
            }                                    
        }
        else if (currentBox.yIndex > target->currentBox.yIndex + 1)
        {
            if(currentBox.index > 0) // Fix incorrect use to "!="            
            {
                currentBox.ocupied = false;
                battlefield->grids[currentBox.index] = currentBox;
                currentBox = battlefield->grids[currentBox.index - 1];
                currentBox.ocupied = true;
                battlefield->grids[currentBox.index] = currentBox;
            
                if(IsEnemy)
                    printf("\nEnemy %s walked up \n", ClassName.c_str());  //Console.WriteLine($"Enemy {EnemyIndex} walked left\n");
                else
                    printf("\nPlayer %s walked up \n", ClassName.c_str());  //Console.WriteLine($"Player {PlayerIndex} walked left\n");
            }
            else
            {
                printf("Current index invalid");
            }
        }
        else if (currentBox.yIndex < target->currentBox.yIndex - 1)
        {
            if(currentBox.index < battlefield->TotalGrids - 1)
            {
                currentBox.ocupied = false;
                battlefield->grids[currentBox.index] = currentBox;
                currentBox = battlefield->grids[currentBox.index + 1];
                currentBox.ocupied = true;
                battlefield->grids[currentBox.index] = currentBox;
            
                if(IsEnemy)
                    printf("\nEnemy %s walked down \n", ClassName.c_str());  //Console.WriteLine($"Enemy {EnemyIndex} walked left\n");
                else
                    printf("\nPlayer %s walked down \n", ClassName.c_str());  //Console.WriteLine($"Player {PlayerIndex} walked left\n");
            }
            else
            {
                printf("Current index invalid");
            }
        }
    }
    return;
}

bool Character::CheckCloseTargets(Grid* battlefield)
{
    return false;
}

void Character::Attack(Character* target) 
{

}

