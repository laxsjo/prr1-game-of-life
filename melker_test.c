#include "melker/askConfig.h"
#include "melker/placeholderState.h"
#include "melker/getTerminalSize.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include <stdbool.h>

int main()
{

    
    BoardState stateInput;
    Vec2 grid = {30, 10};
    
    /*
    //Placeholder values for placeholder state
    stateInput.cells[10][10];
    stateInput.playerPos.x = 7;
    stateInput.playerPos.y = 3;
    stateInput.screenSize.x = 100;
    stateInput.screenSize.y = 150;
    */
    /*
    getTerminalSize();

    makePlaceholderState(&stateInput, &grid);
    
    askConfig(&stateInput);
    */

    Vec2 screenSize = getTerminalSize();

    printf("Terminal size: %dx%d\n", screenSize.x, screenSize.y);

    return 0;
}