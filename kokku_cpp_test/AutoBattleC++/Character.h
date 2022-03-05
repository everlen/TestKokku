#pragma once
#include "Grid.h"
#include "Character.h"
#include "Types.h"
#include <string>

using namespace std; //transfer namespace to from cpp file to header

class Character
{
public:

    Character(Types::CharacterClass characterClass);
    ~Character();
    
    float Health;
    float BaseDamage;
    float DamageMultiplier;
    int PlayerIndex;
    string ClassName; //Add your class name to better control

    //Character Target{ get; set; }
    Character* target;
    //GridBox currentBox;
    Types::GridBox currentBox;
    
    bool IsDead;
    char Icon;
    bool IsEnemy = true;

//Functions
    
    bool TakeDamage(float amount);

    int getIndex(vector<Types::GridBox*> v, int index);

    void Die();

    void WalkTo(bool CanWalk);

    void StartTurn(Grid* battlefield);

    bool CheckCloseTargets(Grid* battlefield);

    void Attack(Character* target);


};

