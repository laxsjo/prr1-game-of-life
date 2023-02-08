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

// Function for loading presets, saved board configs, and creating new boards
void askConfig(BoardState *state)
{

    char loadCreate = '*';
    char input[40];

    BoardState board;

    while (true)
    {
        printf("Would you like to load a previously saved, player-made board configuration, load a preset, or create a new board? (S/P/C)\n");
        scanf("%s", input); // S for Saved player-mades, P for Presets, and C for Creating new boards

        if (input[0] == 'S')
        {

            int boardChoice;
            char **names;
            int len = getAvailableSaveNames(&names);
            if (len == 0)
            {
                printf("Sorry, there were no saves available.\n");
                continue;
            }
            // printf("Okay! Which board would you like to simulate of the ones mentioned below?\n");

            printf("Available boards:\n");
            for (int i = 0; i < len; i++)
            {
                printf("%d: ", i + 1);
                printf("%s\n", names[i]);
            }
            printf("Choose a number: ");

            // printf("1. ???\n2. ___\n");
            scanf("%d", &boardChoice);

            char *name = names[boardChoice];

            int result = loadBoard(state, name);
            if (result == LOAD_RESULT_FILE_MISSING)
            {
                panic("couldn't find expected saves file");
            }
            if (result == LOAD_RESULT_NAME_NOT_FOUND)
            {
                panic("couldn't find choosen save");
            }
            state->saveName = name;

            startEditor(state, name);

            saveBoard(state, name);

            break;

            // if (boardChoice == 1)
            // {

            //     //Fix below!!!!!!!!!!!!!!!!!!!!!!!!
            //     int result = loadBoard(&board, "board1");
            //     if (result == LOAD_RESULT_FILE_MISSING)
            //     {
            //         panic("file not found!");
            //     }
            //     else if (result == LOAD_RESULT_NAME_NOT_FOUND)
            //     {
            //         panic("save does not exist");
            //     }
            //     startGame(state);
            // }
            // else if(boardChoice == 2){
            //     int result = loadBoard(&board, "board2");
            //     if (result == LOAD_RESULT_FILE_MISSING)
            //     {
            //         panic("file not found!");
            //     }
            //     else if (result == LOAD_RESULT_NAME_NOT_FOUND)
            //     {
            //         panic("save does not exist");
            //     }
            // }
        }
        else if (input[0] == 'P')
        {
            panic("not implemented");
            // printf("-Load preset board list function here-\n");
        }
        else if (input[0] == 'C')
        {
            // TODO: This memory will leak!
            char *name = malloc(41);
            printf("Please enter a name for the new board:\n> ");
            scanf("%s", name);
            bool **cells = createEmptyBoardCells((Vec2){1, 1});
            *state = (BoardState){
                cells,
                (Vec2){1, 1},
                (Vec2){0, 0},
                NULL,
                name,
            };

            startEditor(state, name);

            saveBoard(state, name);

            break;
        }
        else
        { // if player inputs faulty response, loop question
            continue;
        }
    }
}