#include "../types.h"

#ifndef _FILES_H
#define _FILES_H

#define LOAD_RESULT_SUCCESS 0
#define LOAD_RESULT_NAME_NOT_FOUND 1
#define LOAD_RESULT_FILE_MISSING 2

/*
Load board save of name saveName from the `.gol.saves.txt` save file.

Returns `LOAD_RESULT_SUCCESS` on success.

Returns `LOAD_RESULT_NAME_NOT_FOUND` when the given save name does not exist.

Returns `LOAD_RESULT_FILE_MISSING` when the `.gol.saves.txt` file does not
exist.

Make sure you check for errors!
*/
int loadBoard(BoardState *board, const char *saveName, const bool isPreset);

/*
Save board to `.gol.saves.txt`
*/
void saveBoard(const BoardState *state);

/// Get a list of save names from `.gol.saves.txt` and store them inside
/// `names`, while returning the length.
///
/// The argument is a **reference** to a **list** of **strings** (each of these
/// represent one of the asterisks in the argument type).
///
/// Make sure to free the name list when you're done using it, you can use the
/// `freeStrList` function in `str_utils.h`.
///
/// # Example
/// ```c
/// #include "rasmus/files.h"
/// #include "rasmus/str_utils.h"
///
/// int main() {
///     char **names;
///
///     size_t len = getAvailableSaveNames(&names);
///
///     // do stuff with names...
///
///     freeStrList(names, len)
/// }
/// ```
size_t getAvailableSaveNames(char ***names, const bool getPresetNames);

#endif