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
        printf("Would you like to load a previously saved board, load a preset, or create a new board [s/p/c]?\n> ");
        scanf("%s", input); // S for Saved player-mades, P for Presets, and C for Creating new boards

        if (input[0] == 's')
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
            boardChoice -= 1;
            if (boardChoice < 0 || boardChoice >= len)
            {
                printf("Please choose a number between 0 and %d\n", len);
                continue;
            }
            char temp;
            scanf("%c", &temp); // scanf("%d") doesn't catch the newline character...

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

            startEditor(state);

            saveBoard(state);

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
        else if (input[0] == 'p')
        {
            panic("not implemented");
            // printf("-Load preset board list function here-\n");
        }
        else if (input[0] == 'c')
        {
            // TODO: This memory will leak! It's probably fine, but still...
            char *name = malloc(41);
            printf("Please enter a name for the new board:\n> ");
            scanf("%s", name);
            bool **cells = createEmptyBoardCells((Vec2){1, 1});
            *state = (BoardState){
                cells,
                (Vec2){1, 1},
                (Vec2){0, 0},
                "",
                name,
            };

            char temp;
            scanf("%c", &temp);

            startEditor(state);

            saveBoard(state);

            break;
        }
        else
        { // if player inputs faulty response, loop question
            continue;
        }
    }
}