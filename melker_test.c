#include "melker/askConfig.h"
#include "melker/placeholderState.h"
#include "melker/getTerminalSize.h"
#include "melker/gameTick.h"
#include "melker/getTerminalSize.h"
#include "melker/simulateCells.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include <stdbool.h>
#include "rasmus/render.h"
#include "rasmus/ansi_term.h"
#include "rasmus/files.h"
#include "rasmus/general.h"
#include "rasmus/input.h"
#include "rasmus/game_logic.h"
#include "rasmus/str_utils.h"

int main()
{

    BoardState stateInput, next;
    stateInput.playerPos = (Vec2){0, 0};
    next.playerPos = (Vec2){0, 0};
    stateInput.message = "c";
    next.message = "c";
    Vec2 size = stateInput.screenSize = (Vec2){60, 30};
    Vec2 nextSize = next.screenSize = (Vec2){60, 30};
    
    /*
    //Placeholder values for placeholder state
    stateInput.cells[10][10];
    stateInput.playerPos.x = 7;
    stateInput.playerPos.y = 3;
    stateInput.screenSize.x = 100;
    stateInput.screenSize.y = 150;
    */

    //getTerminalSize();
    bool stopDummyBool = false;

    srand(time(NULL));

    makePlaceholderState(&stateInput);
    makePlaceholderState(&next);
    for(int y = 0; y < stateInput.screenSize.y; y++){
        for(int x = 0; x < stateInput.screenSize.x; x++){
            printf("%d ",stateInput.cells[y][x]); 
        }
        printf("\n");
    }
    printf("\n");
    //simulateCells(&stateInput, &next);

    
    int loopCount = 0;
    while(stopDummyBool != true){
        //printf("Loop %d:\n", loopCount);
        simulateCells(&stateInput, &next);
        //gameTick(&stateInput);

        //Print output of sim
        printf("Output of loop %d:\n", loopCount);
        for(int y = 0; y < next.screenSize.y; y++){
            for(int x = 0; x < next.screenSize.x; x++){
                printf("%d ", next.cells[y][x]); 
            }
            printf("\n");
        }
        printf("\n");

        stateInput = next;

        sleep(1);
        loopCount++;
        //clearScreen();
    }
    

   
    

    //askConfig(&stateInput);

    //askConfig(&stateInput);
/*
    initBoardDisplay();

    bool stopSim = false;

    while (stopSim != true)
    {
        printf("DEBUG\n");
        stopSim = gameTick(&stateInput, &next);
    }

    cleanUp();

*/


    return 0;
}