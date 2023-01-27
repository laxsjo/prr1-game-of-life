#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../types.h"
#include <stdbool.h>

//Function for loading presets, saved board configs, and creating new boards
void askConfig(BoardState *state){

    BoardState stateExample = *state;

    char loadCreate = '*';

    while(loadCreate != 'S' && loadCreate != 'P' && loadCreate != 'C'){
        printf("Would you like to load a previously saved, player-made board configuration, load a preset, or create a new board? (S/P/C)\n");
        scanf(" %c", &loadCreate); //S for Saved player-mades, P for Presets, and C for Creating new boards

        if(loadCreate == 'S'){
            printf("-Load player-made board function here-\n");

        }else if(loadCreate == 'P'){
            printf("-Load preset board list function here-\n");

        }else if(loadCreate == 'C'){
            printf("-Board creation function here-\n");

        }else{ //if player inputs faulty response, loop question
            printf("That doesn't work!! Please try again...\n");
            sleep(1);
            continue;
        }
    }
}