#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "app.h"

Field **generateGrid(int n)
{
    Field **grid = malloc(sizeof(Field *) * n);

    for (int i = 0; i < n; i++)
    {
        grid[i] = calloc(n, sizeof(Field));
    }

    return grid;
}

void freeGrid(Field **grid, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(grid[i]);
    }
    free(grid);
}

void placeMines(Field **grid, int n, int mines)
{
    int placed = 0;
    while (placed < mines)
    {
        int r = rand() % n;
        int c = rand() % n;

        if (!grid[r][c].mine)
        {
            grid[r][c].mine = 1;
            placed++;
        }
    }
}

int getField(Field **grid, int n, int r, int c)
{
    if (r < 0 || r >= n || c < 0 || c >= n)
    {
        return 0;
    }

    if (grid[r][c].mine)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int getAdjacentMines(Field **grid, int n, int r, int c)
{
    int adjacentMines = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (j == 0 && i == 0)
                continue;

            if (getField(grid, n, (r + i), (c + j)))
            {
                adjacentMines++;
            }
        }
    }

    return adjacentMines;
}

void calculateAdjacentCounts(Field **grid, int n)
{
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            grid[r][c].adjacent = getAdjacentMines(grid, n, r, c);
        }
    }
}

void printGrid(Field **grid, int n)
{
    printf("\033[H\033[J");
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (grid[r][c].flagged)
            {
                printf("%c ", 'F');
            }
            else if (grid[r][c].revealed)
            {
                printf("%c ", grid[r][c].mine ? 'X' : '0' + grid[r][c].adjacent);
            }
            else
            {
                printf("# ");
            }
        }
        printf("\n");
    }
}