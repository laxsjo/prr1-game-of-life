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

bool gameTick(BoardState *state, bool **newCells)
{

    //simulate all the existing cells on the board
    simulateCells(state, newCells);
    for (size_t x = 0; x < state->screenSize.x; x++)
    {
        for (size_t y = 0; y < state->screenSize.y; y++)
        {
            state->cells[y][x] = newCells[y][x];
        }
    }

    //if player presses 'stop'-button, return true, signalizing that the simulation should stop
    bool stop = takeInputs(state, false);
    if (stop == true)
    {
        return true;
    }

    return false;
}