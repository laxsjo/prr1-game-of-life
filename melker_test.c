#include "melker/askConfig.h"
#include "melker/placeholderState.h"
#include "melker/getTerminalSize.h"
#include "melker/gameTick.h"
#include "melker/getTerminalSize.h"
#include "melker/simulateCells.h"
#include "melker/startGame.h"
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
#include <time.h>
/*
void startGame(BoardState *state, BoardState *newState){
    
    int usleep(useconds_t usec);

    initBoardDisplay();

    bool stopSim = false;
    int firstLoopCheck = 0;

    while (stopSim != true)
    {
        if(firstLoopCheck == 0){
            renderBoard(newState);
            sleep(2);
            firstLoopCheck++;
        }
        stopSim = gameTick(state, newState);
        state = newState;
        
        renderBoard(newState);
        
        //sleep(1);
        usleep(200000);
    }

    cleanUp();
}
*/

int main()
{
    BoardState stateInput;
    /*
    stateInput.playerPos = (Vec2){0, 0};
    next.playerPos = (Vec2){0, 0};
    stateInput.message = "c";
    next.message = "c";
    Vec2 size = stateInput.screenSize = (Vec2){100, 40};
    Vec2 nextSize = next.screenSize = (Vec2){100, 40};
    */




    //HERE, DO THIS, FIX THE CONFIG THING!!!
    //askConfig(stateInput, next);


    
    loadBoard(&stateInput, "board3");
    
    startGame(&stateInput);


    /*
   for(int y = 0; y < stateInput.screenSize.y; y++){
        for(int x = 0; x < stateInput.screenSize.x; x++){
            printf("%d ",stateInput.cells[y][x]); 
        }
        printf("\n");
    }
    printf("\n");
    */
   

    //getTerminalSize();
    //bool stopDummyBool = false;

    //srand(time(NULL));

    //makePlaceholderState(&stateInput);
    //makePlaceholderState(&next);
    /*for(int y = 0; y < stateInput.screenSize.y; y++){
        for(int x = 0; x < stateInput.screenSize.x; x++){
            printf("%d ",stateInput.cells[y][x]); 
        }
        printf("\n");
    }
    printf("\n");
    */
    //simulateCells(&stateInput, &next);

    /*
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
    
    */

    //askConfig(&stateInput);

    //askConfig(&stateInput);
    

    //startGame(&stateInput, &next);
    



    return 0;
}