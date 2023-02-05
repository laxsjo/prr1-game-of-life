#include "../types.h"

#ifndef _GAME_LOGIC_H
#define _GAME_LOGIC_H

bool pointInsideBoard(const BoardState *state, const Vec2 point);

bool takeInputs(BoardState *state, bool allowEdit);

void resizeBoard(BoardState *state, Vec2 newSize);

void startEditor(BoardState *state, char *boardName);

#endif