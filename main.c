#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "types.h"
#include "melker/startGame.h"
#include "melker/askConfig.h"

int main()
{
    BoardState state;

    askConfig(&state);

    startGame(&state);

    return 0;
}