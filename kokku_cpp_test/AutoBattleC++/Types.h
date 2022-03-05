#pragma once
class Types
{
public:

    struct GridBox
    {
        int XIndex;
        int YIndex;
        bool Ocupied;
        int Index; //Rename this variable

        GridBox(int AuxXIndex, int AuxYIndex, bool AuxOcupied, int AuxIndex) //I changed the constructor to more simple version
        {
            XIndex = AuxXIndex;
            YIndex = AuxYIndex;
            Ocupied = AuxOcupied;
            Index = AuxIndex;
        }
        GridBox() //I add the constructor with more simple version
        {
            XIndex = -1;
            YIndex = -1;
            Ocupied = false;
            Index = -1;
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

