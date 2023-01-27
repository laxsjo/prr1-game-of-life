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

    // list_char_t *list = NULL;
    // push_back_char(&list, 'A');
    // push_back_char(&list, 'B');
    // push_back_char(&list, 'C');
    // push_back_char(&list, 'D');
    // push_back_char(&list, '\0');

    // printf("string: %s", list->array);

    // createDummyState(&state);
    // Vec2 size = {100, 20};
    // printf("worked: %i\n", result);
    // printf("size: (%i, %i)\n", state.screenSize.x, state.screenSize.y);
    // printf("%u\n", state.cells[0][0]);
    // printf("worked2\n");

    // for (size_t y = 0; y < state.screenSize.y; y++)
    // {
    //     for (size_t x = 0; x < state.screenSize.x; x++)
    //     {
    //         // printf("worked\n");
    //         printf("%u ", state.cells[y][x]);
    //     }
    //     printf("\n");
    // }

    // renderBoard(&state);

    initBoardDisplay();

    // state.playerPos.y = 3;
    // renderBoard(&state);

    // while (getchar() == -1)
    // {
    //     msleep(10);
    // }

    while (!dummyTick(&state))
    {
    }
    saveBoard(&state, "board1");

    cleanUp();

    return 0;
}