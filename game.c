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

void getRidOfZeroes(Field **grid, int n, int r, int c)
{
    for (int r = -1; r <= 1; r++)
    {
        for (int c = -1; c <= 1; c++)
        {
            if (r == 0 && c == 0)
                continue;

            if (!grid[r][c].revealed)
            {
                grid[r][c].revealed = 1;
            }

            if (grid[r][c].adjacent == 0)
            {
                getRidOfZeroes(grid, n, r, c);
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
            grid[r][c].flagged == 0 ? 1 : 0;
        }
        else if (!grid[r][c].mine && action == 'R')
        {
            grid[r][c].revealed = 1;
            if (grid[r][c].adjacent == 0)
            {
                getRidOfZeroes(grid, n, r, c);
            }
        }
        else if (grid[r][c].flagged && action == 'R')
        {
            printf("This field is flagged!");
        }
        else
        {
            isAlive = 0;
            grid[r][c].revealed = 1;
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