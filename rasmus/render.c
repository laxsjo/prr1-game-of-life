// #include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../types.h"
#include "stdio.h"
#include "ansi_term.h"
#include "general.h"
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

// evil global variable: you can't tell me what to do! >:)
char *buffer = NULL;
size_t bufferSize = 0;
Vec2 bufferScreenSize = {0, 0};
size_t bufferIndex = 0;

size_t getBufferSize(const Vec2 screenSize)
{
    size_t size = 0;

    size += ((2 + 5) * screenSize.x) * screenSize.y; // cell size: two spaces + change bg color sequence len
    size += screenSize.y;                            // account for newlines

    // this is very unsafe...
    size += screenSize.x * 2 + 1; // account for top message with a lot of extra margin (there may be zero width characters or unicode characters) + newline at end

    size += 3; // account for move cursor home sequence
    size += 1; // account for terminating null byte
    size *= 3; // some debug leeway

    return size;
}
void allocateBuffer(const Vec2 screenSize)
{
    size_t size = getBufferSize(screenSize);

    buffer = malloc(size);
    bufferSize = size;
    bufferScreenSize = screenSize;
}

void resetBuffer()
{
    bufferIndex = 0;
}

void writeBuffer(const char *string)
{
    size_t len = strlen(string);
    if (bufferIndex + len > bufferSize)
    {
        panic("ran out of buffer size");
    }

    memcpy(buffer + bufferIndex, string, len);

    bufferIndex += len;
}

void closeBuffer()
{
    if (bufferIndex >= bufferSize)
    {
        panic("ran out of buffer size");
    }

    buffer[bufferIndex++] = '\0';
}

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

The final solution seems to have been to create a separate buffer string, which
I write to during the rendering process, which I then finnally print at the end,
ensuring that everything is output in sync correctly

source: https://stackoverflow.com/a/71933775/15507414

*/
void renderBoard(BoardState *state)
{
    Vec2 trueSize = getTerminalSize();

    if (buffer == NULL || !vec2Eq(bufferScreenSize, trueSize))
    {
        allocateBuffer(trueSize);
    }
    resetBuffer();

    writeBuffer(SEQ_MOVE_CURSOR_HOME);

    if (state->message != NULL)
    {
        // TODO: automatically clip message to terminal width
        writeBuffer(state->message);
    }
    writeBuffer("\n");

    char *defaultBgFormat = getSetFormatColor(BG_COLOR_DEFAULT);
    char *whiteBgFormat = getSetFormatColor(BG_COLOR_WHITE);
    char *redBgFormat = getSetFormatColor(BG_COLOR_RED);
    char *greenBgFormat = getSetFormatColor(BG_COLOR_GREEN);

    size_t lines = 0;
    for (size_t y = 0; y < trueSize.y - 1; y++)
    {
        for (size_t x = 0; x < trueSize.x; x++)
        {
            if (x >= state->screenSize.x || y >= state->screenSize.y)
            {
                writeBuffer(defaultBgFormat);
                writeBuffer("  ");
                continue;
            }
            u_int8_t cell = (state->cells)[y][x];
            bool shouldLive = (state->shouldLive)[y][x];

            char *colorFormat;
            Rgb playerColor;

            if (shouldLive)
            {
                playerColor = PLAYER_OVERLAY_COLOR;
            }
            else
            {
                playerColor = PLAYER_COLOR;
            }
            if (cell)
            {
                if (shouldLive)
                {
                    colorFormat = greenBgFormat;
                }
                else
                {
                    colorFormat = redBgFormat;
                }
            }
            else
            {
                if (shouldLive)
                {
                    colorFormat = greenBgFormat;
                }
                else
                {
                    colorFormat = defaultBgFormat;
                }
            }

            if (state->playerPos.x == x && state->playerPos.y == y)
            {
                char *playerFormat = getSetFormatBgRgb(playerColor);
                writeBuffer(playerFormat);
            }
            else
            {
                writeBuffer(colorFormat);
            }
            // if (cell)
            //     cell = 5;
            char temp[5];
            sprintf(temp, "%d ", (u_int8_t)cell);
            writeBuffer(temp);
            // writeBuffer("  ");
        }
        if (y + 1 < trueSize.y - 1)
        {
            writeBuffer("\n");
        }
        lines++;
    }
    closeBuffer();
    free(defaultBgFormat);
    free(whiteBgFormat);

    printf("%s", buffer);
}