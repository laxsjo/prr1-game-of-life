#include "../types.h"

#ifndef _GAME_LOGIC_H
#define _GAME_LOGIC_H

bool pointInsideBoard(const BoardState *state, const Vec2 point);

bool takeInputs(BoardState *state, bool allowEdit);

/// Change the size of board.
/// Clips the board content, or pads it with zeros as necessary.
void resizeBoard(BoardState *state, Vec2 newSize);

/// Start editor, allowing user to edit board.
/// When this function returns, state is ready to be used for the simulation.
void startEditor(BoardState *state, char *boardName);

#endif