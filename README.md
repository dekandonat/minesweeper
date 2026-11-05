# Minesweeper in C

A console-based Minesweeper game written in C.

## Requirements

- Windows
- GCC

## Build

Open PowerShell in the project folder and run:

```powershell
gcc -Wall -Wextra app.c setup.c game.c -o minesweeper
```

## Run

```powershell
.\minesweeper.exe
```

## How to Play

1. Choose the grid size when the game starts (minimum: **11**).
2. Enter the **row** number, then the **column** number of the field you want to interact with.
3. Choose an action:

| Key | Action                     |
| --- | -------------------------- |
| `R` | Reveal the selected field  |
| `F` | Flag (or unflag) the field |

Reveal every field that does not contain a mine to win. Reveal a mine and you lose.
