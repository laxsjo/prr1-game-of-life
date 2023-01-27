#include "../types.h"

#ifndef _GAME_LOGIC_H
#define _GAME_LOGIC_H

bool pointInsideBoard(const BoardState *state, const Vec2 point);

bool takeInputs(BoardState *state, bool allowEdit);

#endif