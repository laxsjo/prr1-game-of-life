#include "../types.h"

#ifndef _INPUT_H
#define _INPUT_H

int kbhit();
int getch();

bool takeInputs(BoardState *state, bool allowEdit);

#endif