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

    resetFormatPrintf();
    moveCursorHomePrintf();

    // write(0, buffer, len);

    // printf("%s", buffer);
}

// void changeFormatColor()

/*
Problem: The render function was generally very inconsistent, sometimes
outputing things in the wrong order.

The problem was that `moveCursorHome()` uses the `write()` command, which,
unlike `printf()`, does not buffer the output. So this might cause
the contents of `write` to be printed before content from `printf`, even if
`printf` was run before `write`.
Ok it seems it's more complicated than that...
Flush stdout after every printf seems to fix the issue. It's obviously not
acceptable because of the performance.

Adding a sleep timer of 10ms to each line also seems to fix the issue. But this
is obviously also too slow.

source: https://stackoverflow.com/a/71933775/15507414

*/
void renderBoard(BoardState *state)
{

    // printf("\x1b[2J");
    moveCursorHomePrintf();

    if (state->message != NULL)
    {
        // TODO: automatically clip message to terminal width
        printf("%s", state->message);
    }
    printf("\n");

    showCursorPrintf();
    // flushCommands();

    // Vec2 trueSize = getTerminalSize();
    Vec2 trueSize = {150, 21};
    // int lastColor = BG_COLOR_DEFAULT;
    size_t lines = 0;
    // Ok so i have to remove one extra line because otherwise the last newline
    // breaks everything since it makes the screen scroll down one character...
    // lso enhltenshoetnseohn
    for (size_t y = 0; y < trueSize.y - 2; y++)
    {
        // if (y >= trueSize.y - 1)
        // {
        //     // continue;
        //     break;
        // }

        /*
        I've been get problems where it overshoots by 1 characters, which is
        why I use `trueSize.x - 1`.
        */
        for (size_t x = 0; x < trueSize.x - 1; x++)
        {
            // if ((x + y) % 2 == 0)
            // {
            //     printf("  ");
            // }
            // else
            // {
            //     printf("##");
            // }
            // continue;

            if (x >= state->screenSize.x || y >= state->screenSize.y)
            {
                // if (x == trueSize.x - 2)
                // {
                //     int last = 0;

                //     setFormatColor(BG_COLOR_DEFAULT);
                //     printf("  ");
                //     // flushCommands();
                //     continue;
                // }
                setFormatColor(BG_COLOR_DEFAULT);
                printf("  ");
                // flushCommands();
                continue;
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
                // flushCommands();
            }
            else
            {
                setFormatColor(color);
                // flushCommands();
            }
            printf("  ");
            // flushCommands();
        }
        printf("\n");
        // msleep(10);
        // flushCommands();
        lines++;
    }
    // flushCommands();
    // msleep(100);

    lines = lines;
}