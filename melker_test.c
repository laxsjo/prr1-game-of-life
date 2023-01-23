#include "melker/melker_example.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include <stdbool.h>

int main()
{
    BoardState stateInput;
    
    stateInput.cells[10][10];
    stateInput.playerPos.x = 7;
    stateInput.playerPos.y = 3;
    stateInput.screenSize.x = 100;
    stateInput.screenSize.y = 150;
    
    askConfig(&stateInput);

    //doStuffMelker();

    return 0;
}