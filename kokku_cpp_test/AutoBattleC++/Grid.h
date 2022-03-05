#pragma once
#include <Vector>
#include "Types.h"

class Grid
{

public:

    Grid(int Lines, int Columns);
    ~Grid(); 

    std::vector<Types::GridBox> grids;

    int xLength;
    int yLength;
    int TotalGrids; // create this variable to better control of last index in vector grids
    
    // prints the matrix that indicates the tiles of the battlefield
    void drawBattlefield(int Lines, int Columns, int PlayerIndexGrid, char PlayerIcon, char EnemyIcon); //Edit parameters to more details of characters
    Types::GridBox GetGridInLocation(int x, int y); // create function to return grid item in X and Y position
};

