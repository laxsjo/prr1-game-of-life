#include "../types.h"

#ifndef _GENERAL_H
#define _GENERAL_H

typedef struct
{
    size_t line;
    const char *file;
    const char *func;
} _LineInfo;

/*
Crash the program, printing a reason string alongside line number and the name of
file and function.

This calls `cleanUp` before exiting.
*/
#define panic(reason) _panic(reason, (const _LineInfo){__LINE__, __FILE__, __func__})

/*
Ready the terminal for rendering the board.

Make sure to call `cleanUp` before ending the program!
*/
void initBoardDisplay();

/*
Reset any terminal flags or similar settings to their default setting.
*/
void cleanUp();

void _panic(const char *reason, const _LineInfo location);

#endif