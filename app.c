#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "app.h"

int main()
{
    srand(time(NULL));

    int n;
    printf("Give the size of the grid: ");
    if (scanf("%d", &n) != 1 || n <= 10)
    {
        printf("Invalid size");
        return 1;
    }

    Field **grid = generateGrid(n);

    placeMines(grid, n, n * n * 15 / 100);
    calculateAdjacentCounts(grid, n);
    startGame(grid, n);
    freeGrid(grid, n);
    return 0;
}