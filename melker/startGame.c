#include "askConfig.h"
#include "placeholderState.h"
#include "getTerminalSize.h"
#include "gameTick.h"
#include "getTerminalSize.h"
#include "simulateCells.h"
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
#include <time.h>

void startGame(BoardState *state)
{
    // add message /Rasmus
    Vec2 size = getTerminalSize();
    size.x *= 2;
    char message[101]; // this should be more than enough, right?...

    //message displayed at the top of the screen while simulation is ongoing
    snprintf(message, 100, "Simulating board '%s'. [Arrow keys]: move cursor, [Enter]/[Esc]: exit", state->saveName);
    message[100] = '\0';
    state->message = message;

    growBoardToWindow(state);

    bool **other;

    other = copyBoardCells(state);

    int usleep(useconds_t usec);

    initBoardDisplay();

    bool stopSim = false;
    int firstLoopCheck = 0;
    //loop the simulation until stopSim is true, this happens when
    //the player presses the 'stop'-button (see comments under gameTick)
    while (stopSim != true)
    {
        if (firstLoopCheck == 0)
        {
            renderBoard(state);
            firstLoopCheck++;
        }
        stopSim = gameTick(state, other);

        //juggle the information/content between states
        bool **temp = state->cells;
        state->cells = other;
        other = temp;

        renderBoard(state);

        usleep(100000);
    }

    cleanUp();
}