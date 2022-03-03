#pragma once
class Types
{
public:

    struct GridBox
    {
        int xIndex;
        int yIndex;
        bool ocupied;
        int Index;

        GridBox(int AuxX, int AuxY, bool AuxOcupied, int AuxIndex) //I changed the name of the parameters for better definition 
        {
            xIndex = AuxX;
            yIndex = AuxY;
            ocupied = AuxOcupied;
            Index = AuxIndex;
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

