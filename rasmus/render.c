// #include <stdlib.h>
#include <unistd.h>

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

/*
Problem: clearScreen is too slow and cause the screen to flash
*/
void clearScreen()
{
    Vec2 size = getTerminalSize();
    // Vec2 size = {8, 4};

    size_t len = (size.x * 2) * size.y + size.y;
    char buffer[len + 1];
    size_t i = 0;

    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {
            // size_t index = y * (size.x + 1) + x;
            // buffer[index] = ' ';
            buffer[i++] = ' ';
            buffer[i++] = ' ';
        }
        // size_t index = (y + 1) * (size.x + 1);
        // buffer[index] = '\n';
        buffer[i++] = '\n';
        // printf("\r\n");
    }
    // buffer[size.x * size.y + size.y] = '\0';
    buffer[i] = '\0';

    size_t spaceCount = 0;
    size_t newlineCount = 0;
    size_t otherCount = 0;
    for (int i = 0; i < len; i++)
    {
        if (buffer[i] == ' ')
        {
            spaceCount++;
        }
        else if (buffer[i] == '\n')
        {
            newlineCount++;
        }
        else
        {
            otherCount++;
        }
    }

    resetFormat();
    moveCursorHome();

    write(0, buffer, len);

    // printf("%s", buffer);
}

void renderBoard(BoardState *state)
{
    moveCursorHome();

    if (state->message != NULL)
    {
        // TODO: automatically clip message to terminal width
        printf("%s", state->message);
    }
    printf("\n");

    Vec2 trueSize = getTerminalSize();
    for (int y = 0; y < trueSize.y - 1; y++)
    {
        // if (y >= trueSize.y - 1)
        // {
        //     // continue;
        //     break;
        // }

        for (int x = 0; x < trueSize.x; x++)
        {
            if (x >= state->screenSize.x || y >= state->screenSize.y)
            {
                setFormatColor(BG_COLOR_DEFAULT);
                printf("  ");
            }
            // if (x >= trueSize.x)
            // {
            //     continue;
            // }
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