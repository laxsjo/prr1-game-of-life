#include <unistd.h>

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

void movePlayerIntoBounds(BoardState *state)
{
    Vec2 trueSize = getDummySize1();

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
    if (state->playerPos.y >= trueSize.y)
    {
        state->playerPos.y = trueSize.y - 1;
    }
}

void movePlayerPos(BoardState *state, const Vec2 newPos)
{
    state->playerPos = newPos;
    movePlayerIntoBounds(state);
}

bool handleInput(const Input input, BoardState *state, const bool allowEdit)
{
    bool test = 0;
    switch (input.type)
    {
    case InputUp:
        movePlayerPos(state, (Vec2){state->playerPos.x, state->playerPos.y - 1});
        break;
    case InputDown:
        movePlayerPos(state, (Vec2){state->playerPos.x, state->playerPos.y + 1});
        break;
    case InputRight:
        movePlayerPos(state, (Vec2){state->playerPos.x + 1, state->playerPos.y});
        break;
    case InputLeft:
        movePlayerPos(state, (Vec2){state->playerPos.x - 1, state->playerPos.y});
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

void startEditor(BoardState *state, char *boardName)
{
    Vec2 size = getTerminalSize();
    char message[size.x + 1];
    snprintf(message, size.x, "Editing board '%s'. [Arrow keys]: move cursor, [Space]: flip selected cell, [Enter]/[Esc]: save and start simulation", boardName);
    message[size.x] = '\0';

    state->message = message;

    initBoardDisplay();

    // clearScreen();

    renderBoard(state);
    // sleep(1);
    // renderBoard(state);
    // renderBoard(state);
    // renderBoard(state);
    // renderBoard(state);
    // renderBoard(state);
    // renderBoard(state);
    // renderBoard(state);
    // renderBoard(state);
    // renderBoard(state);
    // renderBoard(state);
    // renderBoard(state);
    // renderBoard(state);
    // renderBoard(state);
    // sleep(1);
    // renderBoard(state);
    // sleep(1);
    // renderBoard(state);
    // sleep(1);
    // renderBoard(state);
    // sleep(1);
    // renderBoard(state);
    // sleep(1);
    // renderBoard(state);
    // sleep(1);
    // renderBoard(state);
    // sleep(1);
    // renderBoard(state);
    // sleep(1);
    // renderBoard(state);
    // sleep(1);
    // renderBoard(state);
    // sleep(1);
    // renderBoard(state);
    // sleep(1);
    // renderBoard(state);
    // sleep(1);
    // renderBoard(state);
    // sleep(1);
    // renderBoard(state);
    // sleep(1);
    // renderBoard(state);
    // sleep(1);
    // renderBoard(state);
    // sleep(1);
    // renderBoard(state);
    // sleep(1);
    // renderBoard(state);
    // sleep(1);
    // renderBoard(state);

    flushCommands();

    // clearScreen();

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