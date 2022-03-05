#include "Grid.h"

Grid::Grid(int Lines, int Columns)
{
    XLength = Lines;
    YLength = Columns;
    TotalGrids = 0;
    //Console.WriteLine("The battle field has been created\n");
    for (int i = 0; i < Lines; i++)
    {
        for (int j = 0; j < Columns; j++)
        {
            Types::GridBox* newBox = new Types::GridBox();
            newBox->Index = Columns * i + j;
            newBox->Ocupied = false;
            newBox->YIndex = j;
            newBox->XIndex = i;
            grids.insert(grids.end(), *newBox); //Fix reference to pointer address
            //Console.Write($"{newBox.Index}\n");
            TotalGrids++;
        }
    }
	//drawBattlefield(Lines, Columns);
}

Grid::~Grid() 
{

}

void Grid::drawBattlefield(int Lines, int Columns, int PlayerIndexGrid, char PlayerIcon, char EnemyIcon) //Update parameters to received Icon info
{
    printf("\n Battlefield Map \n");
    int AuxCount = 0;
    for (int i = 0; i < Lines; i++)
    {
        for (int j = 0; j < Columns; j++)
        {
            Types::GridBox* currentgrid = &grids[AuxCount]; // use the variable to control progress index
            if (currentgrid->Ocupied)
            {
                if(currentgrid->Index == PlayerIndexGrid) //Print character info with your icon
                    printf("[%c]\t", PlayerIcon);
                else
                    printf("[%c]\t", EnemyIcon);
            }
            else
            {
                printf("[ ]\t");
            }
            AuxCount++;
        }
        printf("\n");
    }
    printf("\n");
}

Types::GridBox Grid::GetGridInLocation(int x, int y)
{
    return grids[YLength * x + y];
}