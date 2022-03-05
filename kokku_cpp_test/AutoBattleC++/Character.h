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
    Character* Target;
    //GridBox currentBox;
    Types::GridBox CurrentBox;
    
    bool IsDead;
    char Icon;
    int Reach;
    bool IsEnemy = true;

//Functions
    
    bool TakeDamage(float amount);

    int getIndex(vector<Types::GridBox*> v, int index);

    void Die();

    void WalkTo(bool CanWalk);

    void StartTurn(Grid* battlefield);

    bool CheckCloseTargets(Grid* battlefield);

    float Attack(Character* target);

    void ApplyLocomotionEffect(Grid* battlefield);
};

