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
    CurrentBox = *new Types::GridBox(); //Fix constructor adding a initialization in this variable
    Target = this; //Fix warning not initializate
    
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
	if ((Health -= amount) <= 0) 
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
        const float CurrentMultiplyDamage = Attack(Character::Target);
        if(CurrentMultiplyDamage > 1)
        {
            printf("CRITICAL EFFECT!!! >>> ");
            int index = std::rand() % 3;
            if(index == 0)
            {
                printf("ATTACKS MOVED THE TARGET... ");
                ApplyLocomotionEffect(battlefield);  
            }            
        }
        Target->TakeDamage(BaseDamage * CurrentMultiplyDamage);
        if(IsEnemy)
        {
            printf("Enemy %s attack the player %s | Damage: %f \n", ClassName.c_str(), Target->ClassName.c_str(), BaseDamage * CurrentMultiplyDamage);
            printf("Player Health: %f\n", Target->Health);            
        }
        else
        {
            printf("Player %s attack the enemy %s | Damage: %f \n", ClassName.c_str(), Target->ClassName.c_str(), BaseDamage * CurrentMultiplyDamage);
            printf("Enemy Health: %f\n", Target->Health);  
        }
    }
    else
    {   // if there is no target close enough, calculates in wich direction this character should move to be closer to a possible target
        if (CurrentBox.XIndex > Target->CurrentBox.XIndex + 1) //Verify if character is in side grid
        {
            if(CurrentBox.XIndex > 0) // Fix incorrect use to "!="            
            {
                CurrentBox.Ocupied = false;
                battlefield->grids[CurrentBox.Index] = CurrentBox;

                CurrentBox = battlefield->GetGridInLocation(CurrentBox.XIndex - 1, CurrentBox.YIndex); //Used this function to find array index in matrix location
                CurrentBox.Ocupied = true;
                battlefield->grids[CurrentBox.Index] = CurrentBox;
                
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
        else if (CurrentBox.XIndex < Target->CurrentBox.XIndex - 1)
        {
            if(CurrentBox.XIndex < battlefield->XLength - 1)
            {
                CurrentBox.Ocupied = false;
                battlefield->grids[CurrentBox.Index] = CurrentBox;
                
                CurrentBox = battlefield->GetGridInLocation(CurrentBox.XIndex + 1, CurrentBox.YIndex);
                CurrentBox.Ocupied = true;
                battlefield->grids[CurrentBox.Index] = CurrentBox;
                
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
        if (CurrentBox.YIndex > Target->CurrentBox.YIndex + 1)
        {
            if(CurrentBox.YIndex > 0) // Fix incorrect use to "!="            
            {
                CurrentBox.Ocupied = false;
                battlefield->grids[CurrentBox.Index] = CurrentBox;
                CurrentBox = battlefield->GetGridInLocation(CurrentBox.XIndex, CurrentBox.YIndex - 1);
                CurrentBox.Ocupied = true;
                battlefield->grids[CurrentBox.Index] = CurrentBox;
            
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
        else if (CurrentBox.YIndex < Target->CurrentBox.YIndex - 1)
        {
            if(CurrentBox.YIndex < battlefield->YLength - 1)
            {
                CurrentBox.Ocupied = false;
                battlefield->grids[CurrentBox.Index] = CurrentBox;
                CurrentBox = battlefield->GetGridInLocation(CurrentBox.XIndex, CurrentBox.YIndex + 1);
                CurrentBox.Ocupied = true;
                battlefield->grids[CurrentBox.Index] = CurrentBox;
            
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
    if (((CurrentBox.XIndex <= Target->CurrentBox.XIndex + Reach && CurrentBox.XIndex >= Target->CurrentBox.XIndex) || (CurrentBox.XIndex >= Target->CurrentBox.XIndex - Reach && CurrentBox.XIndex <= Target->CurrentBox.XIndex)) && ((CurrentBox.YIndex <= Target->CurrentBox.YIndex + Reach && CurrentBox.YIndex >= Target->CurrentBox.YIndex)|| (CurrentBox.YIndex >= Target->CurrentBox.YIndex - Reach && CurrentBox.YIndex <= Target->CurrentBox.YIndex))) //Verify if character is in side grid
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
        CurrentMultipyDamage = DamageMultiplier; //Attack critical effect
    }    
    return CurrentMultipyDamage;
}

void Character::ApplyLocomotionEffect(Grid* battlefield)
{
    Target->CurrentBox.Ocupied = false; // Force moved when take a critical attack
    battlefield->grids[Target->CurrentBox.Index] = Target->CurrentBox;
    int AuxXIndex = Target->CurrentBox.XIndex;
    int AuxYIndex = Target->CurrentBox.YIndex;
    if(Target->CurrentBox.XIndex > CurrentBox.XIndex && Target->CurrentBox.XIndex < battlefield->XLength-1)
    {
        AuxXIndex = Target->CurrentBox.XIndex + 1;
    }
    else if(Target->CurrentBox.XIndex < CurrentBox.XIndex && Target->CurrentBox.XIndex > 0)
    {
        AuxXIndex = Target->CurrentBox.XIndex - 1;
    }
    if(Target->CurrentBox.YIndex > CurrentBox.YIndex && Target->CurrentBox.YIndex < battlefield->YLength-1)
    {
        AuxYIndex = Target->CurrentBox.YIndex + 1;
    }
    else if(Target->CurrentBox.YIndex < CurrentBox.YIndex && Target->CurrentBox.YIndex > 0)
    {
        AuxYIndex = Target->CurrentBox.YIndex - 1;
    }
            
    Target->CurrentBox = battlefield->GetGridInLocation(AuxXIndex, AuxYIndex);
    Target->CurrentBox.Ocupied = true;
    battlefield->grids[Target->CurrentBox.Index] = Target->CurrentBox;
}
