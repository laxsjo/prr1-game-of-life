#include "../types.h"
#include "input.h"

bool pointInsideBoard(const BoardState *state, const Vec2 point)
{
    return point.x >= 0 && point.y >= 0 && point.x < state->screenSize.x && point.y < state->screenSize.y;
}

void movePlayerPos(BoardState *state, const Vec2 newPos)
{
    if (pointInsideBoard(state, newPos))
    {
        state->playerPos = newPos;
    }
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
    /* Problem: I need a dynamic list, because I don't know how many inputs we
    will receive, and I need to package them up into a single array

    I used this answer from SO: https://stackoverflow.com/a/46351960/15507414
    It had a really nice explanation, and a simple yet extensive implementation.
    */

    list_char_t *bytes = NULL;

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

    for (size_t i = 0; i < inputs.len; i++)
    {
        handleInput(inputs.inputs[i], state, allowEdit);
    }
}