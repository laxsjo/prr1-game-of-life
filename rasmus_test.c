#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "types.h"
#include "rasmus/render.h"
#include "rasmus/ansi_term.h"
#include "rasmus/files.h"
#include "rasmus/general.h"
#include "rasmus/input.h"
#include "rasmus/game_logic.h"
#include "rasmus/str_utils.h"
#include "melker/startGame.h"

bool dummyTick(BoardState *state)
{
    if (takeInputs(state, true))
    {
        return true;
    }

    clearScreen();

    renderBoard(state);

    msleep(100);

    return false;
}

int main(int argc)
{
    BoardState state;
    int result = loadBoard(&state, "board1");
    if (result == LOAD_RESULT_FILE_MISSING)
    {
        panic("file not found!");
    }
    else if (result == LOAD_RESULT_NAME_NOT_FOUND)
    {
        panic("save does not exist");
    }

    startEditor(&state, "board1");

    char *message = "Running simulation for 'board1'";
    state.message = message;
    startGame(&state);

    return 0;
}