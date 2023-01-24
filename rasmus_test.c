#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "types.h"
#include "rasmus/render.h"
#include "rasmus/ansi_term.h"
#include "rasmus/files.h"

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

int main(int argc)
{
    BoardState state;
    loadBoard(&state, "board1");
    // createDummyState(&state);
    Vec2 size = {100, 20};

    renderBoard(&state);

    // while (true)
    // {
    //     sleep(1);

    //     for (int x = 0; x < size.x; x++)
    //     {
    //         for (int y = 0; y < size.y; y++)
    //         {
    //             state.cells[y][x] = rand() % 2;
    //         }
    //     }
    //     clearScreen();
    //     renderBoard(&state);
    // }
    // char test;

    // // scanf("%c", &test);
    // // printf("got %c", test);

    // enterNonCanonicalMode();

    // scanf("%c", &test);
    // printf("got %c\n", test);

    // printf("hi\n");
    // printf("hello\n");

    // exitNonCanonicalMode();

    return 0;
}