#include "../types.h"
#include "stdio.h"
#include "ansi_term.h"

// Dummy function, while melkers creates the actual function.
Vec2 getScreenSize()
{
    // I want to write this on one line... :(
    Vec2 out = {100, 14};
    return out;
}

void clearScreen()
{
    Vec2 size = getScreenSize();
    moveCursorHome();

    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.y; x++)
        {
            printf(" ");
        }
        printf("\r\n");
    }
}

void renderBoard(BoardState *state)
{
    moveCursorHome();

    Vec2 trueSize = getScreenSize();
    for (int y = 0; y < state->screenSize.y; y++)
    {
        if (y >= trueSize.y)
        {
            continue;
        }

        for (int x = 0; x < state->screenSize.x; x++)
        {
            if (x >= trueSize.x)
            {
                continue;
            }
            bool cell = (state->cells)[y][x];

            if (cell)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\r\n");
    }
}