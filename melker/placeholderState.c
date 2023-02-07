#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../types.h"
#include <stdbool.h>
#include <time.h>

int makePlaceholderState(BoardState *state)
{
    Vec2 gridSize = state->screenSize;
    Vec2 playerPos = {0, 0};

    u_int8_t(**coords) = malloc(sizeof(u_int8_t *) * gridSize.y);
    for (int i = 0; i < gridSize.y; i++)
    {
        coords[i] = malloc(sizeof(u_int8_t) * gridSize.x);
    }

    for (int x = 0; x < gridSize.x; x++)
    {
        for (int y = 0; y < gridSize.y; y++)
        {

            int randomizer = rand() % 7;
            if (randomizer == 0 || randomizer > 1)
            {
                coords[y][x] = 0;
            }
            else
            {
                coords[y][x] = 1;
            }

            // coords[y][x] = rand() % 2;
        }
    }

    u_int8_t **coordsPointer = (u_int8_t **)coords;

    coords[0][0] = true;

    BoardState outState = {
        (u_int8_t **)coords,
        gridSize,
        {0, 0},
    };
    *state = outState;

    /*for(int y = 0; y < gridSize.y; y++){
        for(int x = 0; x < gridSize.x; x++){
            printf("%d ",coords[y][x]);
        }
        printf("\n");
    }
    printf("\n");*/
}