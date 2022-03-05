// AutoBattleC++.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//
#include "BattleField.h"
#include <iostream>
#include <time.h>

int main()
{
    int seed = 0;
    seed = static_cast<int>(time(0));
    srand(seed); // Seed to random generator value
    BattleField* battleField = new(BattleField);
    battleField->Setup();
    battleField->StartGame();
}


