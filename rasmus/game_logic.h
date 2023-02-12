#include "../types.h"

#ifndef _GAME_LOGIC_H
#define _GAME_LOGIC_H

/*
Check if the point is within the visual board bounds.

The visual board bounds is the smallest of the screen size and literal size of
the board in memory.
*/
bool pointInsideBoard(const BoardState *state, const Vec2 point);

/*
Take inputs, and change state appropriately.
This function returns `true` when the user wants to close/finish the current
view.
*/
bool takeInputs(BoardState *state, bool allowEdit);

/// Todo: finish documentation
bool **createEmptyBoardCells(Vec2 size);

/// Change the size of board.
/// Clips the board content, or pads it with zeros as necessary.
void resizeBoard(BoardState *state, Vec2 newSize);

/// Create a copy of a boards content.
bool **copyBoardCells(const BoardState *state);

/// Create a copy of board and it's content.
BoardState copyBoard(const BoardState *state);

/// Make board at least as large as window.
void growBoardToWindow(BoardState *state);

/// Start editor, allowing user to edit board.
/// When this function returns, state is ready to be used for the simulation.
void startEditor(BoardState *state);

#endif