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
    snprintf(message, 100, "Simulating board '%s'. [Arrow keys]: move cursor, [Enter]/[Esc]: exit", state->saveName);
    message[100] = '\0';
    state->message = message;
    // // !Potential problem: since we have two states constantly being flipped
    // // between `state` and `newState`, the other copy doesn't have the
    // // metadata of the original.
    // Nvm, since, we copy the board, the information (more accurately the
    // pointers to the messages, so the information is shared!) is copied...

    BoardState other;
    BoardState *newState;

    other = copyBoard(state);
    newState = &other;

    int usleep(useconds_t usec);

    initBoardDisplay();

    bool stopSim = false;
    int firstLoopCheck = 0;

    while (stopSim != true)
    {
        if (firstLoopCheck == 0)
        {
            renderBoard(newState);
            // sleep(2); // I don't think we should have this, or at least not
            // for this long /Rasmus
            firstLoopCheck++;
        }
        stopSim = gameTick(state, newState);
        BoardState *temp = state;
        state = newState;
        newState = temp;

        renderBoard(newState);

        // sleep(1);
        usleep(200000);
    }

    cleanUp();
}