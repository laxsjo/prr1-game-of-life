#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
// #include <types.h>
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
    int sum = 0;

    // TO BE CONTINUED, FIX SO Y CAN BE -1 WITHOUT SEG FAULT
    // PROBLEM: Going out of an array's bounds causes immediate seg faults and it needs to be worked around
    // SOLUTION: Noticed that the targeted cell coords when adding/not adding a point to the sum (line 47)
    // got a negative input which caused a seg fault, instead I decided to target
    // state->cells[cellToSimulate.y + i][cellToSimulate.x + j] instead which fixed it!
    // printf("Target cell: (%d, %d)\n\n", cellToSimulate.y, cellToSimulate.x);
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }

            if ((cellToSimulate.y + i) >= 0 && (cellToSimulate.x + j) >= 0 && (cellToSimulate.y + i) < state->screenSize.y && (cellToSimulate.x + j) < state->screenSize.x)
            {
                if (state->cells[cellToSimulate.y + i][cellToSimulate.x + j] == 1)
                {
                    sum++;
                }
            }
        }
    }

    // if (state->cells[cellToSimulate.y][cellToSimulate.x] == 1)
    // {
    //     sum--;
    // }

    return sum;
}

void simulateCells(BoardState *state, BoardState *newState)
{

    // makePlaceholderState(&newState);

    // Simulate board changes to next per cell
    for (int i = 0; i < state->screenSize.y; i++)
    {

        for (int j = 0; j < state->screenSize.x; j++)
        {

            int neighborSum = simulateSingleCell(state, (Vec2){j, i});

            if (state->playerPos.x == j && state->playerPos.y == i)
            {
                newState->cells[i][j] = (u_int8_t)neighborSum;
            }
            // if (newState->cells[i][j] > 0 && neighborSum > 0)
            // {
            //     newState->cells[i][j] = (u_int8_t)neighborSum;
            // }

            // if (newState->cells[i][j])
            // {
            //     newState->cells[i][j] = (u_int8_t)neighborSum;
            //     if (neighborSum < 2 || neighborSum > 3)
            //     {

            //         newState->cells[i][j] = 0;
            //     }
            // }
            // else if (!newState->cells[i][j])
            // {
            //     if (neighborSum == 3)
            //     {

            //         newState->cells[i][j] = (u_int8_t)neighborSum;
            //     }
            // }
        }
    }
}
