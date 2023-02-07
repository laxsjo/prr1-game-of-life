#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "../types.h"
#include <stdbool.h>
#include "../rasmus/render.h"
#include "../rasmus/ansi_term.h"
#include "../rasmus/files.h"
#include "../rasmus/general.h"
#include "../rasmus/input.h"
#include "../rasmus/game_logic.h"
#include "../rasmus/str_utils.h"
#include "startGame.h"

//Function for loading presets, saved board configs, and creating new boards
void askConfig(BoardState *state, BoardState *newState){

    char loadCreate = '*';

    BoardState board;

    while(loadCreate != 'S' && loadCreate != 'P' && loadCreate != 'C'){
        printf("Would you like to load a previously saved, player-made board configuration, load a preset, or create a new board? (S/P/C)\n");
        scanf(" %c", &loadCreate); //S for Saved player-mades, P for Presets, and C for Creating new boards

        if(loadCreate == 'S'){

            int boardChoice;
            printf("Okay! Which board would you like to simulate of the ones mentioned below?\n");
            printf("1. ???\n2. ___\n");
            scanf("%d", &boardChoice);

            if(boardChoice == 1){
                
                //Fix below!!!!!!!!!!!!!!!!!!!!!!!!
                int result = loadBoard(&board, "board1");
                if (result == LOAD_RESULT_FILE_MISSING)
                {
                    panic("file not found!");
                }
                else if (result == LOAD_RESULT_NAME_NOT_FOUND)
                {
                    panic("save does not exist");
                }
                startGame(state, newState);
            }
            else if(boardChoice == 2){
                int result = loadBoard(&board, "board2");
                if (result == LOAD_RESULT_FILE_MISSING)
                {
                    panic("file not found!");
                }
                else if (result == LOAD_RESULT_NAME_NOT_FOUND)
                {
                    panic("save does not exist");
                }
            }
            

        }else if(loadCreate == 'P'){
            printf("-Load preset board list function here-\n");

        }else if(loadCreate == 'C'){
            printf("startEditor();\n");

        }else{ //if player inputs faulty response, loop question
            printf("That doesn't work!! Please try again...\n");
            sleep(1);
            continue;
        }
    }
}