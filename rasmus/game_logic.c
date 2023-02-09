#include <unistd.h>

#include "game_logic.h"
#include "../types.h"
#include "input.h"
#include "general.h"
#include "render.h"
#include "ansi_term.h"
#include "../melker/getTerminalSize.h"

// Dummy function, while melkers creates the actual function.
Vec2 getDummySize1()
{
    // I want to write this on one line... :(
    Vec2 out = {100, 14};
    return out;
}

bool pointInsideBoard(const BoardState *state, const Vec2 point)
{
    return point.x >= 0 && point.y >= 0 && point.x < state->screenSize.x && point.y < state->screenSize.y;
}

bool pointInsideWindow(const Vec2 point)
{
    if (point.x < 0 || point.y < 0)
    {
        return false;
    }

    Vec2 screenSize = getTerminalSize();

    return point.x < screenSize.x && point.y < screenSize.y - 1;
}

void movePlayerIntoBounds(BoardState *state)
{
    Vec2 trueSize = getTerminalSize();

    if (state->playerPos.x < 0)
    {
        state->playerPos.x = 0;
    }
    if (state->playerPos.y < 0)
    {
        state->playerPos.y = 0;
    }

    if (state->playerPos.x >= state->screenSize.x)
    {
        state->playerPos.x = state->screenSize.x - 1;
    }
    if (state->playerPos.y >= state->screenSize.y)
    {
        state->playerPos.y = state->screenSize.y - 1;
    }

    if (state->playerPos.x >= trueSize.x)
    {
        state->playerPos.x = trueSize.x - 1;
    }
    if (state->playerPos.y >= trueSize.y - 1)
    {
        state->playerPos.y = trueSize.y - 2;
    }
}

void movePlayerPos(BoardState *state, const Vec2 newPos, const bool autoResize)
{
    if (autoResize && newPos.x >= 0 && newPos.y >= 0 && !pointInsideBoard(state, newPos) && pointInsideWindow(newPos))
    {
        Vec2 newSize;

        if (newPos.x >= state->screenSize.x)
        {
            newSize = (Vec2){state->screenSize.x * 2, state->screenSize.y};
        }
        else
        {
            newSize = (Vec2){state->screenSize.x, state->screenSize.y * 2};
        }

        resizeBoard(state, newSize);
    }

    state->playerPos = newPos;
    movePlayerIntoBounds(state);
}

bool handleInput(const Input input, BoardState *state, const bool allowEdit)
{
    bool test = 0;
    switch (input.type)
    {
    case InputUp:
        movePlayerPos(state, (Vec2){state->playerPos.x, state->playerPos.y - 1}, allowEdit);
        break;
    case InputDown:
        movePlayerPos(state, (Vec2){state->playerPos.x, state->playerPos.y + 1}, allowEdit);
        break;
    case InputRight:
        movePlayerPos(state, (Vec2){state->playerPos.x + 1, state->playerPos.y}, allowEdit);
        break;
    case InputLeft:
        movePlayerPos(state, (Vec2){state->playerPos.x - 1, state->playerPos.y}, allowEdit);
        break;
    case InputNormal:
        test = true;
        char key = input.normalKey;
        switch (key)
        {
        case ' ':
            if (allowEdit)
            {
                // flip cell value
                bool *cell = &state->cells[state->playerPos.y][state->playerPos.x];
                *cell = !*cell;
            }
            break;
        case '\e':
        case '\n':
            return true;
        default:
            break;
        }

    default:
        break;
    }

    return false;
}

bool takeInputs(BoardState *state, bool allowEdit)
{
    // in case terminal window got resized
    movePlayerIntoBounds(state);

    /* Problem: I need a dynamic list, because I don't know how many inputs we
    will receive, and I need to package them up into a single array

    I used this answer from SO: https://stackoverflow.com/a/46351960/15507414
    It had a really nice explanation, and a simple yet extensive implementation.
    */

    list_char_t *bytes = new_char_list();

    while (true)
    {
        int input = getchar();
        if (input == -1)
        {
            break;
        }
        push_back_char(&bytes, (char)input);
    }

    InputList inputs;
    parseInputBytes(bytes->array, bytes->len, &inputs);
    free(bytes);

    for (size_t i = 0; i < inputs.len; i++)
    {
        if (handleInput(inputs.inputs[i], state, allowEdit))
        {
            return true;
        }
    }
    freeInputList(inputs);
    return false;
}

bool **createEmptyBoardCells(Vec2 size)
{
    bool **newCells = malloc(sizeof(*newCells) * size.y);
    for (size_t y = 0; y < size.y; y++)
    {
        newCells[y] = calloc(size.x, sizeof(**newCells));
    }

    return newCells;
}

void resizeBoard(BoardState *state, Vec2 newSize)
{
    bool **newCells = malloc(sizeof(*newCells) * newSize.y);
    for (size_t y = 0; y < newSize.y; y++)
    {
        newCells[y] = malloc(sizeof(**newCells) * newSize.x);
    }

    for (size_t y = 0; y < newSize.y; y++)
    {
        for (size_t x = 0; x < newSize.x; x++)
        {
            if (pointInsideBoard(state, (Vec2){x, y}))
            {
                newCells[y][x] = state->cells[y][x];
            }
            else
            {
                newCells[y][x] = 0;
            }
        }
    }

    freeBoardCells(state->cells, state->screenSize);

    state->cells = newCells;
    state->screenSize = newSize;
}

bool **copyBoardCells(const BoardState *state)
{
    // allocate new cells
    bool **newCells = malloc(sizeof(*newCells) * state->screenSize.y);
    for (size_t i = 0; i < state->screenSize.y; i++)
    {
        newCells[i] = malloc(sizeof(**newCells) * state->screenSize.x);
    }

    // copy values
    for (size_t x = 0; x < state->screenSize.x; x++)
    {
        for (size_t y = 0; y < state->screenSize.y; y++)
        {
            newCells[y][x] = state->cells[y][x];
        }
    }

    return newCells;
}

BoardState copyBoard(const BoardState *state)
{
    BoardState out = *state;

    // allocate new cells
    bool **newCells = copyBoardCells(state);

    out.cells = newCells;

    return out;
}

void startEditor(BoardState *state)
{
    const char *messageSave = "save and start simulation";
    const char *messageNoSave = "start simulation";
    const char *enterMessage;
    if (state->shouldSave)
    {
        enterMessage = messageSave;
    }
    else
    {
        enterMessage = messageNoSave;
    }
    Vec2 size = getTerminalSize();
    char message[size.x * 2 + 1];
    snprintf(message, size.x * 2, "Editing board '%s'. [Arrow keys]: move cursor, [Space]: edit cell, [Enter]/[Esc]: %s", state->saveName, enterMessage);
    message[size.x * 2] = '\0';

    state->message = message;

    initBoardDisplay();

    while (true)
    {
        if (takeInputs(state, true))
        {
            break;
        }

        // not necessary
        // clearScreen();

        renderBoard(state);
    }

    cleanUp();
}