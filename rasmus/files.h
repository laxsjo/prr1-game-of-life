#include "../types.h"

#ifndef _FILES_H
#define _FILES_H

#define LOAD_RESULT_SUCCESS 0
#define LOAD_RESULT_NAME_NOT_FOUND 1
#define LOAD_RESULT_FILE_MISSING 2

int loadBoard(BoardState *board, const char *saveName);

void saveBoard(const BoardState *state, char *saveName);

#endif