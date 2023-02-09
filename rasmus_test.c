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
#include "rasmus/str_utils.h"
#include "melker/startGame.h"

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

bool randomBoolWithProbability(float p)
{
    // source: https://stackoverflow.com/a/65427060/15507414
    int percent = (int)(p * 100.);

    int result = rand() % 100;
    return result < percent;
}

int main(int argc, char **argv)
{
    float probability;
    if (argc < 2)
    {
        panic("no probability argument given");
    }
    sscanf(argv[1], "%f", &probability);

    srand(time(0));
    for (size_t i = 0; i < 20; i++)
    {
        char buffer[61];
        buffer[60] = '\0';

        for (size_t j = 0; j < 60; j++)
        {
            bool random = randomBoolWithProbability(probability);
            if (random)
            {
                buffer[j] = '1';
            }
            else
            {
                buffer[j] = '0';
            }
        }
        printf("%s\n", buffer);
    }

    return 0;
}