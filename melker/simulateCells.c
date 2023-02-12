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

//simulates every individual cell based on its 8 neighboring cells
int simulateSingleCell(BoardState *state, Vec2 cellToSimulate)
{
    //the sum of the neighboring cells' contents
    int sum = 0;

    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            //if the targeted cell is the one to be simulated;
            //continue without accounting for it's contents
            if (i == 0 && j == 0)
            {
                continue;
            }
            
            //if the targeted neighbor cell is within the boundaries AND is alive, increase the sum by 1
            //if the first condition isn't met; the targeted neighbor cell is out of bounds
            if ((cellToSimulate.y + i) >= 0 && (cellToSimulate.x + j) >= 0 && (cellToSimulate.y + i) < state->screenSize.y && (cellToSimulate.x + j) < state->screenSize.x)
            {
                if (state->cells[cellToSimulate.y + i][cellToSimulate.x + j] == 1)
                {
                    sum++;
                }
            }
        }
    }

    //return the total sum of all the neighbors
    return sum;
}

void simulateCells(BoardState *state, bool **newCells)
{
    //simulate board and apply changes to the new generation
    for (int i = 0; i < state->screenSize.y; i++)
    {

        for (int j = 0; j < state->screenSize.x; j++)
        {
            int neighborSum = simulateSingleCell(state, (Vec2){j, i});

            if (state->cells[i][j])
            {
                //rules for live cells
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
                //rules for dead cells
                if (neighborSum == 3)
                {
                    newCells[i][j] = 1;
                }
            }
        }
    }
}
