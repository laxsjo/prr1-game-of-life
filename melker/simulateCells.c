#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../types.h"
#include "gameTick.h"
#include "getTerminalSize.h"
#include <stdbool.h>
#include "../rasmus/render.h"
#include "../rasmus/ansi_term.h"
#include "../rasmus/files.h"
#include "../rasmus/general.h"
#include "../rasmus/input.h"
#include "../rasmus/game_logic.h"
#include "../rasmus/str_utils.h"
#include "askConfig.h"
#include "placeholderState.h"
#include "getTerminalSize.h"
#include "gameTick.h"
#include "getTerminalSize.h"
#include "simulateCells.h"

int simulateSingleCell(BoardState *state, Vec2 cellToSimulate)
{

    // printf("Cell to simulate: %d, %d\n\n", cellToSimulate.y, cellToSimulate.x);

    int sum = 0;

    // TO BE CONTINUED, FIX SO Y CAN BE -1 WITHOUT SEG FAULT
    // PROBLEM: Going out of an array's bounds causes immediate seg faults and it needs to be worked around
    // SOLUTION: Noticed that the targeted cell coords when adding/not adding a point to the sum (line 47)
    // got a negative input which caused a seg fault, instead I decided to target
    // state->cells[cellToSimulate.y + i][cellToSimulate.x + j] instead which fixed it!
    // printf("Target cell: (%d, %d)\n\n", cellToSimulate.y, cellToSimulate.x);
    for (int i = -1; i < 2; i++)
    {
        /*if((cellToSimulate.x - 1) < 0 || (cellToSimulate.x + 1 > state->screenSize.x) || (cellToSimulate.y - 1) < 0 || (cellToSimulate.y + 1 > state->screenSize.y)){
            state->cells[cellToSimulate.y][cellToSimulate.x] = NULL;
        }*/

        for (int j = -1; j < 2; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }
            // printf("%d, %d\n", i, j);
            // printf("CellToSimulate coords: %d, %d\n\n", cellToSimulate.y, cellToSimulate.x);
            /*
            if(cellToSimulate.y + i >= 0  && cellToSimulate.x + j >= 0 && cellToSimulate.y + i <= state->screenSize.y && cellToSimulate.x + j <= state->screenSize.x){
                //if(cellToSimulate.y + i <= state->screenSize.y && cellToSimulate.x + j <= state->screenSize.x){
                    if(state->cells[i][j] == 1){
                        sum++;
                    }
                //}
            }*/

            if ((cellToSimulate.y + i) >= 0 && (cellToSimulate.x + j) >= 0 && (cellToSimulate.y + i) < state->screenSize.y && (cellToSimulate.x + j) < state->screenSize.x)
            {
                if (state->cells[cellToSimulate.y + i][cellToSimulate.x + j] == 1)
                {
                    sum++;
                }
            }

            // printf("%d y %d x\n\n", (cellToSimulate.y + i), (cellToSimulate.x + j));
        }
    }

    // printf("Sum: %d\n\n", sum);
    // if (state->cells[cellToSimulate.y][cellToSimulate.x] == 1)
    // {
    //     sum--;
    //     // printf("New Sum: %d\n\n", sum);
    // }
    // printf("Sum: %d\n\n", sum);

    return sum;
}

void simulateCells(BoardState *state, bool **newCells)
{
    // Simulate board changes to next per cell
    for (int i = 0; i < state->screenSize.y; i++)
    {

        for (int j = 0; j < state->screenSize.x; j++)
        {
            int neighborSum = simulateSingleCell(state, (Vec2){j, i});

            if (state->cells[i][j])
            {

                if (neighborSum == 3 || neighborSum == 2)
                {
                    newCells[i][j] = 1;
                }
                else if (neighborSum < 2 || neighborSum > 3)
                {
                    newCells[i][j] = 0;
                }
            }
            else
            {
                if (neighborSum == 3)
                {
                    newCells[i][j] = 1;
                }
            }
        }
    }
}
