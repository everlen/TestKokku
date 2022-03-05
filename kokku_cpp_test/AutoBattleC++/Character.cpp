#include "Character.h" //I cleaned out the redundant includes and kept them only in the header file
#include <vector>
#include <algorithm>

Character::Character(Types::CharacterClass characterClass)
{    
    //Set a base value in variables on class
    Health = 100;
    BaseDamage = 20;
    PlayerIndex = 0;
    DamageMultiplier = 2.0f;
    Reach = 1;
    IsDead = false;
    Icon = 'X';
    string ClassNames[] = {"Paladin", "Warrior", "Cleric", "Archer"}; //Add vector of class names
    ClassName = ClassNames[characterClass -1]; //Set name Class in character constructor
    currentBox = *new Types::GridBox(); //Fix constructor adding a initialization in this variable
    target = this; //Fix warning not initializate
    
    if(characterClass == 1) //Class attributes config
    {
        Health = 140;
    }
    else if(characterClass == 2)
    {
        DamageMultiplier = 3;
        BaseDamage = 30;
    }
    else if(characterClass == 3)
    {
        Health = 110;
        Reach = 2;
    }
    else if(characterClass == 4)
    {
        Health = 80;
        DamageMultiplier = 3;
        Reach = 3;
    }
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
        const float CurrentDamage = Attack(Character::target);

        if(IsEnemy)
        {
            printf("Enemy %s attack the player %s | Damage: %f \n", ClassName.c_str(), target->ClassName.c_str(), CurrentDamage);
            printf("Player Health: %f\n", target->Health);            
        }
        else
        {
            printf("Player %s attack the enemy %s | Damage: %f \n", ClassName.c_str(), target->ClassName.c_str(), CurrentDamage);
            printf("Enemy Health: %f\n", target->Health);  
        }
    }
    else
    {   // if there is no target close enough, calculates in wich direction this character should move to be closer to a possible target
        if (currentBox.xIndex > target->currentBox.xIndex + 1) //Verify if character is in side grid
        {
            if(currentBox.xIndex > 0) // Fix incorrect use to "!="            
            {
                currentBox.ocupied = false;
                battlefield->grids[currentBox.index] = currentBox;

                currentBox = battlefield->GetGridInLocation(currentBox.xIndex - 1, currentBox.yIndex); //Used this function to find array index in matrix location
                currentBox.ocupied = true;
                battlefield->grids[currentBox.index] = currentBox;
                
                if(IsEnemy)
                    printf("Enemy %s walked up \n", ClassName.c_str());  //Console.WriteLine($"Player {PlayerIndex} walked left\n");
                else
                    printf("Player %s walked up \n", ClassName.c_str());  //Console.WriteLine($"Player {PlayerIndex} walked left\n");
            }
            else
            {
                printf("Current index invalid");
            }                
        }
        else if (currentBox.xIndex < target->currentBox.xIndex - 1)
        {
            if(currentBox.xIndex < battlefield->xLength - 1)
            {
                currentBox.ocupied = false;
                battlefield->grids[currentBox.index] = currentBox;
                
                currentBox = battlefield->GetGridInLocation(currentBox.xIndex + 1, currentBox.yIndex);
                currentBox.ocupied = true;
                battlefield->grids[currentBox.index] = currentBox;
                
                if(IsEnemy)
                    printf("Enemy %s walked down \n", ClassName.c_str());  //Console.WriteLine($"Player {PlayerIndex} walked left\n");
                else
                    printf("Player %s walked down \n", ClassName.c_str());  //Console.WriteLine($"Player {PlayerIndex} walked left\n");
            }
            else
            {
                printf("Current index invalid\n");
            }                                    
        }
        else if (currentBox.yIndex > target->currentBox.yIndex + 1)
        {
            if(currentBox.yIndex > 0) // Fix incorrect use to "!="            
            {
                currentBox.ocupied = false;
                battlefield->grids[currentBox.index] = currentBox;
                currentBox = battlefield->GetGridInLocation(currentBox.xIndex, currentBox.yIndex - 1);
                currentBox.ocupied = true;
                battlefield->grids[currentBox.index] = currentBox;
            
                if(IsEnemy)
                    printf("Enemy %s walked left \n", ClassName.c_str());  //Console.WriteLine($"Enemy {EnemyIndex} walked left\n");
                else
                    printf("Player %s walked left \n", ClassName.c_str());  //Console.WriteLine($"Player {PlayerIndex} walked left\n");
            }
            else
            {
                printf("Current index invalid");
            }
        }
        else if (currentBox.yIndex < target->currentBox.yIndex - 1)
        {
            if(currentBox.yIndex < battlefield->yLength - 1)
            {
                currentBox.ocupied = false;
                battlefield->grids[currentBox.index] = currentBox;
                currentBox = battlefield->GetGridInLocation(currentBox.xIndex, currentBox.yIndex + 1);
                currentBox.ocupied = true;
                battlefield->grids[currentBox.index] = currentBox;
            
                if(IsEnemy)
                    printf("Enemy %s walked right \n", ClassName.c_str());  //Console.WriteLine($"Enemy {EnemyIndex} walked left\n");
                else
                    printf("Player %s walked right \n", ClassName.c_str());  //Console.WriteLine($"Player {PlayerIndex} walked left\n");
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
    if (((currentBox.xIndex <= target->currentBox.xIndex + Reach && currentBox.xIndex >= target->currentBox.xIndex) || (currentBox.xIndex >= target->currentBox.xIndex - Reach && currentBox.xIndex <= target->currentBox.xIndex)) && ((currentBox.yIndex <= target->currentBox.yIndex + Reach && currentBox.yIndex >= target->currentBox.yIndex)|| (currentBox.yIndex >= target->currentBox.yIndex - Reach && currentBox.yIndex <= target->currentBox.yIndex))) //Verify if character is in side grid
        return true;
    else    
        return false;
}

float Character::Attack(Character* target) 
{
    float CurrentMultipyDamage = 1.0f;
    int index = std::rand() % 5;
    if(index == 0)
    {
        printf("CRITICAL EFFECT!!! >>> ");
        CurrentMultipyDamage = DamageMultiplier; //Attack critical effect
    }

    target->Health = target->Health - BaseDamage * CurrentMultipyDamage;
    
    return BaseDamage * CurrentMultipyDamage;
}

