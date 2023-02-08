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

void createDummyState(BoardState *state)
{
    Vec2 size = {100, 20};

    // source: https://stackoverflow.com/a/36890904/15507414
    bool(**cells) = malloc(sizeof(bool *) * size.y);
    for (int i = 0; i < size.y; i++)
    {
        cells[i] = malloc(sizeof(bool) * size.x);
    }
    for (int x = 0; x < size.x; x++)
    {
        for (int y = 0; y < size.y; y++)
        {
            cells[y][x] = rand() % 2;
        }
    }

    bool **cellsPointer = (bool **)cells;

    cells[0][0] = true;

    BoardState outState = {
        (bool **)cells,
        size,
        {0, 0},
    };
    *state = outState;
}

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

    // test copyBoard
    BoardState stateCopy = copyBoard(&state);

    char *message = "Running simulation for 'board1'";
    stateCopy.message = message;
    startGame(&stateCopy);

    return 0;
}