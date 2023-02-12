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
#include <ctype.h>
#include <errno.h>
#include <termios.h>
#include "intro.h"

// Function for loading presets, saved board configs, and creating new boards
void askConfig(BoardState *state)
{

    char loadCreate = '*';
    char input[40];
    char throwaway[10];

    BoardState board;

    while (true)
    {
        speakGen(7, "Would you like to load a previously saved board, load a preset, or create a new board? [s/p/c]\r\n", false);
        printFace(false);
        printf("Would you like to load a previously saved board, load a preset, or create a new board? [s/p/c]\r\n");

        scanf("%s", input); // S for Saved player-mades, P for Presets, and C for Creating new boards

        if (input[0] == 's')
        {

            int boardChoice;
            char **names;
            int usleep(useconds_t usec);
            int len = getAvailableSaveNames(&names, false);

            if (len == 0)
            {
            
                system("clear");

                printFace(false);
                printf("Hmmm...");
                usleep(200000);
                fflush(stdout);

                printf("Let's see...\n");
                usleep(1000000);

                system("clear");

                speakGen(6, "Sorry, there were no saves available.\n", true);
                printFace(true);
                usleep(500000);

                system("clear");

                continue;
            }
            // printf("Okay! Which board would you like to simulate of the ones mentioned below?\n");
                    
            printf("Available boards:\n");
            for (int i = 0; i < len; i++)
            {
                printf("%d: ", i + 1);
                printf("%s\n", names[i]);
                usleep(200000);
            }
            printf("Choose a number: ");

            // printf("1. ???\n2. ___\n");
            scanf("%d", &boardChoice);
            boardChoice -= 1;
            if (boardChoice < 0 || boardChoice >= len)
            {
                printf("Please choose a number between 1 and %d\n", len);
                sleep(2);
                continue;
            }
            char temp;
            scanf("%c", &temp); // scanf("%d") doesn't catch the newline character...

            char *name = names[boardChoice];

            int result = loadBoard(state, name, false);
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
        }
        else if (input[0] == 'p')
        {
            int boardChoice;
            char **names;
            int len = getAvailableSaveNames(&names, true);
            if (len == 0)
            {
                system("clear");

                printFace(false);
                printf("Hmmm...");
                usleep(200000);
                fflush(stdout);

                printf("Let's see...\n");
                usleep(1000000);

                system("clear");

                speakGen(6, "Sorry, there were no presets available.\n", true);
                printFace(true);
                usleep(500000);

                system("clear");

                continue;
            }
            // printf("Okay! Which board would you like to simulate of the ones mentioned below?\n");

            printf("Available presets:\n");
            for (int i = 0; i < len; i++)
            {
                printf("%d: ", i + 1);
                printf("%s\n", names[i]);
                usleep(200000);
            }
            printf("Choose a number: ");

            scanf("%d", &boardChoice);
            boardChoice -= 1;
            if (boardChoice < 0 || boardChoice >= len)
            {
                system("clear");

                printFace(true);
                printf("Please choose a number between 1 and %d\n", len);
                sleep(2);
                system("clear");
                continue;
            }
            char temp;
            scanf("%c", &temp); // scanf("%d") doesn't catch the newline character...

            char *name = names[boardChoice];

            int result = loadBoard(state, name, true);
            if (result == LOAD_RESULT_FILE_MISSING)
            {
                panic("couldn't find expected saves file");
            }
            if (result == LOAD_RESULT_NAME_NOT_FOUND)
            {
                panic("couldn't find choosen save");
            }
            state->saveName = name;

            printf("Do you wan't to save any modifications you make to this preset? [y/n]\n> ");
            scanf("%s", input);
            scanf("%c", throwaway); // get rid of trailing newline
            if (input[0] == 'y')
            {
                printf("Please enter a new name\n> ");
                name = malloc(41);
                scanf("%s", name);
                scanf("%c", throwaway); // get rid of trailing newline

                state->saveName = name;
                state->shouldSave = true;
            }
            else
            {
                state->shouldSave = false;
            }

            startEditor(state);

            if (state->shouldSave)
            {
                saveBoard(state);
            }

            break;
        }
        else if (input[0] == 'c')
        {
            // TODO: This memory will leak! It's probably fine, but still...
            char *name = malloc(41);
            speakGen(6, "Please enter a name for the new board:\n", false);
            printFace(false);
            scanf("%s", name);
            bool **cells = createEmptyBoardCells((Vec2){1, 1});
            *state = (BoardState){
                cells,
                (Vec2){1, 1},
                (Vec2){0, 0},
                "",
                name,
                false,
                true,
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