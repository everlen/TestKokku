#pragma once
class Types
{
public:

    struct GridBox
    {
        int xIndex;
        int yIndex;
        bool ocupied;
        int index; //Rename this variable

        GridBox(int auxXIndex, int auxYIndex, bool auxOcupied, int auxIndex) //I changed the constructor to more simple version
        {
            xIndex = auxXIndex;
            yIndex = auxYIndex;
            ocupied = auxOcupied;
            index = auxIndex;
        }
        GridBox() //I add the constructor with more simple version
        {
            xIndex = -1;
            yIndex = -1;
            ocupied = false;
            index = -1;
        }
    };

    enum CharacterClass
    {
        Paladin = 1,
        Warrior = 2,
        Cleric = 3,
        Archer = 4
    };

};

