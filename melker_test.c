#include "melker/askConfig.h"
#include "melker/placeholderState.h"
#include "melker/getTerminalSize.h"
#include "melker/gameTick.h"
#include "melker/getTerminalSize.h"
#include "melker/simulateCells.h"
#include "melker/startGame.h"
#include "melker/intro.h"
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

    //runIntro();

    askConfig(&stateInput);
    
    return 0;
}