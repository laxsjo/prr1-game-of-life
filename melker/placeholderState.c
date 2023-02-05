#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../types.h"
#include <stdbool.h>
#include <time.h>

int makePlaceholderState(BoardState *state){
    Vec2 gridSize = state->screenSize;
    Vec2 playerPos = {0, 0};

    bool (**coords) = malloc(sizeof(bool *)* gridSize.y);
    for(int i = 0; i < gridSize.y; i++){
        coords[i] = malloc(sizeof(bool) * gridSize.x);
    }

    for(int x = 0; x < gridSize.x; x++){
        for(int y = 0; y < gridSize.y; y++){
            //coords[y][x] = rand() % 4;
            coords[y][x] = rand() % 2;
        }
    }

    bool **coordsPointer = (bool **)coords;

    coords[0][0] = true;

    BoardState outState = {
        (bool **)coords,
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