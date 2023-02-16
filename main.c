#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "types.h"
#include "melker/startGame.h"
#include "melker/askConfig.h"
#include "melker/intro.h"
#include "rasmus/render.h"
#include "rasmus/ansi_term.h"
#include "rasmus/files.h"
#include "rasmus/general.h"
#include "rasmus/input.h"
#include "rasmus/game_logic.h"
#include "rasmus/str_utils.h"

int main()
{
    BoardState state;

    setupCrashHandler();

    activateAlternativeBuffer();

    char skip[41];

    printf("Skip intro? [y/n]");
    scanf("%s", skip);
    system("clear");

    if (skip[0] != 'y')
    {
        runIntro();
    }

    askConfig(&state);

    startGame(&state);

    disableAlternativeBuffer();

    return 0;
}