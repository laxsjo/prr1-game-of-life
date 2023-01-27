#include "../types.h"
#include "stdio.h"
#include "ansi_term.h"
#include "../melker/getTerminalSize.h"

const Rgb PLAYER_COLOR = {65, 216, 226};
const Rgb PLAYER_OVERLAY_COLOR = {114, 255, 224};

// Dummy function, while melkers creates the actual function.
Vec2 getDummySize2()
{
    // I want to write this on one line... :(
    Vec2 out = {100, 14};
    return out;
}

void clearScreen()
{
    Vec2 size = getDummySize2();
    resetFormat();
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

    Vec2 trueSize = getDummySize2();
    for (int y = 0; y < state->screenSize.y; y++)
    {
        if (y >= trueSize.y)
        {
            // continue;
            break;
        }

        for (int x = 0; x < state->screenSize.x; x++)
        {
            if (x >= trueSize.x)
            {
                continue;
            }
            bool cell = (state->cells)[y][x];

            int color;
            Rgb playerColor;

            if (cell)
            {
                color = BG_COLOR_WHITE;
                playerColor = PLAYER_OVERLAY_COLOR;
            }
            else
            {
                color = BG_COLOR_DEFAULT;
                playerColor = PLAYER_COLOR;
            }

            if (state->playerPos.x == x && state->playerPos.y == y)
            {
                setFormatBgRgb(playerColor);
            }
            else
            {
                setFormatColor(color);
            }
            printf("  ");
        }
        printf("\r\n");
    }
}