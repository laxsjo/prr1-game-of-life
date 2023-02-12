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
#include "intro.h"
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
        // enable raw mode and ask player for board options
        //  enableRawMode();
        //  speakGen(7, "Would you like to load a previously saved board, load a preset, or create a new board? [s/p/c]\r\n", false);
        printFace(false);
        printf("Would you like to load a previously saved board, load a preset, or create a new board? [s/p/c]\r\n");

        // loop until player inputs 's', 'p', or 'c'
        while (1)
        {

            char c = '\0';
            if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN)
                die("read");
            /*
            if(iscntrl(c)) {
                printf("%d\r\n", c);
            }else{
                printf("%d ('%c')\r\n", c, c);
            }
            */
            if (c == 's' || c == 'p' || c == 'c')
            {
                input[0] = c;
                break;
            }
        }
        disableRawMode();

        if (input[0] == 's')
        {

            int boardChoice;
            char **names;
            int usleep(useconds_t usec);
            int len = getAvailableSaveNames(&names, false);

            // fail in case there are no previous save files
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

            // display available saved boards
            printf("Available boards:\n");
            for (int i = 0; i < len; i++)
            {
                printf("%d: ", i + 1);
                printf("%s\n", names[i]);
            }
            printf("Choose a number: ");

            scanf("%d", &boardChoice);
            boardChoice -= 1;

            // loop question if player inputs faulty response
            if (boardChoice < 0 && len != 1 || boardChoice >= len && len != 1)
            {
                printf("Please choose a number between 1-%d!\n", len);
                sleep(2);
                continue;
            }
            else if (boardChoice < 0 && len == 1 || boardChoice >= len && len == 1)
            {
                printf("Please choose number %d!\n", len);
                sleep(2);
                continue;
            }

            char temp;
            scanf("%c", &temp); // scanf("%d") doesn't catch the newline character...

            char *name = names[boardChoice];

            // load the board that the player chose and crash if file name
            // wasn't found or if save file couldn't be found
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
            // if there are no presets available
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

            // display presets
            printf("Available presets:\n");
            for (int i = 0; i < len; i++)
            {
                printf("%d: ", i + 1);
                printf("%s\n", names[i]);
            }
            printf("Choose a number:\n> ");
            scanf("%d", &boardChoice);

            // special board with special interaction from Gunther (the host character)
            if (boardChoice == 13)
            {
                system("clear");
                speakGen(1, "Please no!\n", true);
                printFace(true);
                usleep(300000);
                system("clear");
                speakGen(5, "Anything but that one..!\n", true);
                printFace(true);
                usleep(500000);

                enableRawMode();

                for (int i = 0; i < 3; i++)
                {
                    printf(".");
                    fflush(stdout);
                    usleep(500000);
                }
                printf("\r\n");

                printf("(Press 'c' to continue regardless...)\r\n");

                while (1)
                {

                    char c = '\0';
                    if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN)
                        die("read");
                    /*
                    if(iscntrl(c)) {
                        printf("%d\r\n", c);
                    }else{
                        printf("%d ('%c')\r\n", c, c);
                    }
                    */
                    if (c == 'c')
                    {
                        break;
                    }
                }
                disableRawMode();
            }
            boardChoice -= 1;
            if (boardChoice < 0 || boardChoice >= len)
            {
                system("clear");

                printFace(true);
                printf("Please choose a number between 1 and %d!\n", len);
                sleep(2);
                system("clear");
                continue;
            }
            char temp;
            scanf("%c", &temp); // scanf("%d") doesn't catch the newline character...

            char *name = names[boardChoice];

            // load board and fail in case file name or file is missing
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

            // let the player make modifications to the presets unless the preset in question
            // is... the forbidden one...
            if (boardChoice != 12)
            {
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
            // ask player for board name
            system("clear");
            char *name = malloc(41);
            speakGen(6, "Please enter a name for the new board:\n", false);
            printFace(false);
            printf("Please enter a name for the new board:\n> ");

            scanf("%s", name);
            usleep(300000);
            system("clear");

            speakGen(2, "Nice name!\n", false);
            printFace(false);
            usleep(400000);
            system("clear");

            speakGen(2, "Bye now!\n", true);
            usleep(200000);

            // create a new, empty board for the player to be able to customize
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