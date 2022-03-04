#pragma once
#include <Vector>
#include "Types.h"

class Grid
{

public:

    Grid(int Lines, int Columns);
    ~Grid(); 

    std::vector<Types::GridBox> grids;

    int xLenght;
    int yLength;
    int TotalGrids; // create this variable to better control of last index in vector grids
    
    // prints the matrix that indicates the tiles of the battlefield
    void drawBattlefield(int Lines, int Columns);
};

