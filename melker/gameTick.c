#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../types.h"
#include "gameTick.h"
#include "getTerminalSize.h"
#include <stdbool.h>
#include "../rasmus/render.h"
#include "../rasmus/ansi_term.h"
#include "../rasmus/files.h"
#include "../rasmus/general.h"
#include "../rasmus/input.h"
#include "../rasmus/game_logic.h"
#include "../rasmus/str_utils.h"
#include "askConfig.h"
#include "placeholderState.h"
#include "getTerminalSize.h"
#include "gameTick.h"
#include "getTerminalSize.h"
#include "simulateCells.h"

bool gameTick(BoardState *state, BoardState *newState){

    //BoardState next;

    simulateCells(state, newState);

    /*
    freeBoardCells(state->cells, state->screenSize);
    state->cells = next.cells;
    */
    

    bool stop = takeInputs(state, false);
    if(stop == true){
        printf("STOP!\n");
        return true;
    }
    
    return false;
}