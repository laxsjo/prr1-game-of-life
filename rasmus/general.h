#include "../types.h"

#ifndef _GENERAL_H
#define _GENERAL_H

typedef struct
{
    size_t line;
    const char *file;
    const char *func;
} _LineInfo;

#define panic(reason) _panic(reason, (const _LineInfo){__LINE__, __FILE__, __func__})

void initBoardDisplay();

void cleanUp();

void _panic(const char *reason, const _LineInfo location);

#endif