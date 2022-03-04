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



void Character::StartTurn(Grid* battlefield) {

    {

        if (CheckCloseTargets(battlefield))
        {
            Attack(Character::target);


            return;
        }
        else
        {   // if there is no target close enough, calculates in wich direction this character should move to be closer to a possible target
            
            
            if (currentBox.xIndex > target->currentBox.xIndex)
            {
                if(currentBox.index - 1 != battlefield->grids.end()->index) // Fix incorrect use to "!="            
                {
                    currentBox.ocupied = false;
                    battlefield->grids[currentBox.index] = currentBox;

                    currentBox = (battlefield->grids[currentBox.index - 1]);
                    currentBox.ocupied = true;
                    battlefield->grids[currentBox.index] = currentBox;
                    //Console.WriteLine($"Player {PlayerIndex} walked left\n");
                    battlefield->drawBattlefield(5, 5);

                    return;
                }
            }
            else if (currentBox.xIndex < target->currentBox.xIndex)
            {
                currentBox.ocupied = false;
                battlefield->grids[currentBox.index] = currentBox;
                currentBox = (battlefield->grids[currentBox.index + 1]);
                return;
                battlefield->grids[currentBox.index] = currentBox;
                //Console.WriteLine($"Player {PlayerIndex} walked right\n");
                battlefield->drawBattlefield(5, 5);
            }

            if (currentBox.yIndex > target->currentBox.yIndex)
            {
                battlefield->drawBattlefield(5, 5);
                currentBox.ocupied = false;
                battlefield->grids[currentBox.index] = currentBox;
                currentBox = battlefield->grids[(currentBox.index - battlefield->xLenght)];
                currentBox.ocupied = true;
                battlefield->grids[currentBox.index] = currentBox;
                //Console.WriteLine($"PlayerB {PlayerIndex} walked up\n");
                return;
            }
            else if (currentBox.yIndex < target->currentBox.yIndex)
            {
                currentBox.ocupied = true;
                battlefield->grids[currentBox.index] = currentBox;
                currentBox = battlefield->grids[currentBox.index + battlefield->xLenght];
                currentBox.ocupied = false;
                battlefield->grids[currentBox.index] = currentBox;
                //Console.WriteLine($"Player {PlayerIndex} walked down\n");
                battlefield->drawBattlefield(5, 5);

                return;
            }
        }
    }
}

bool Character::CheckCloseTargets(Grid* battlefield)
{
    return false;
}

void Character::Attack(Character* target) 
{

}

