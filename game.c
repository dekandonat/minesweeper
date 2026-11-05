#include <stdio.h>
#include "app.h"

void getUserInput(int n, int *r, int *c, char *action)
{
    printf("Give the number of the selected row: ");
    do
    {
        scanf("%d", r);
        if (*r <= 0 || *r > n)
        {
            printf("Invalid row, try again: ");
        }
    } while (*r <= 0 || *r > n);

    printf("Give the number of the selected column: ");
    do
    {
        scanf("%d", c);

        if (*c <= 0 || *c > n)
        {
            printf("Invalid column, try again: ");
        }
    } while (*c <= 0 || *c > n);

    (*r)--;
    (*c)--;

    printf("R - Reveal\nF - Flag\nSelect your action: ");
    do
    {
        scanf(" %c", action);
        if (*action != 'R' && *action != 'F')
        {
            printf("Invalid action, try again: ");
        }
    } while (*action != 'R' && *action != 'F');
}

int checkForGameEnd(Field **grid, int n)
{
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            if (!grid[r][c].mine && !grid[r][c].revealed)
                return 0;
    return 1;
}

void getRidOfZeroes(Field **grid, int n, int row, int column)
{
    for (int r = -1; r <= 1; r++)
    {
        for (int c = -1; c <= 1; c++)
        {
            if (r == 0 && c == 0)
                continue;

            if (row + r < 0 || row + r >= n || column + c < 0 || column + c >= n)
                continue;

            if (!grid[row + r][column + c].revealed)
            {
                grid[row + r][column + c].revealed = 1;
                if (grid[row + r][column + c].adjacent == 0)
                {

                    getRidOfZeroes(grid, n, row + r, column + c);
                }
            }
        }
    }
}

void revealAllBombs(Field **grid, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j].mine && !grid[i][j].revealed)
            {
                grid[i][j].revealed = 1;
            }
        }
    }
}

void startGame(Field **grid, int n)
{
    int isAlive = 1;
    do
    {
        printGrid(grid, n);
        int r;
        int c;
        char action;
        getUserInput(n, &r, &c, &action);

        if (action == 'F')
        {
            if (grid[r][c].flagged == 0)
            {
                grid[r][c].flagged = 1;
            }
            else
            {
                grid[r][c].flagged = 0;
            }
        }
        else if (grid[r][c].flagged && action == 'R')
        {
            printf("This field is flagged!");
        }
        else if (!grid[r][c].mine && action == 'R')
        {
            grid[r][c].revealed = 1;
            if (grid[r][c].adjacent == 0)
            {
                getRidOfZeroes(grid, n, r, c);
            }
        }
        else
        {
            isAlive = 0;
            grid[r][c].revealed = 1;
            revealAllBombs(grid, n);
            printGrid(grid, n);
            printf("You Lost!");
        }

        if (checkForGameEnd(grid, n))
        {
            printGrid(grid, n);
            printf("You Won!");
            isAlive = 0;
        }
    } while (isAlive);
}