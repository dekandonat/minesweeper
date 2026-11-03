#ifndef APP_H
#define APP_H

typedef struct
{
    int mine;     //? 1 if its a mine
    int adjacent; //?adjacent mines
    int revealed; //? 1 if revealed
    int flagged;  //? 1 if flagged
} Field;

Field **generateGrid(int n);

void freeGrid(Field **grid, int n);

void placeMines(Field **grid, int n, int mines);

int getField(Field **grid, int n, int r, int c);

void calculateAdjacentCounts(Field **grid, int n);

void printGrid(Field **grid, int n);

#endif