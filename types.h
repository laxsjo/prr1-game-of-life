#include <stdbool.h>

// To avoid problems when the header is included in multiple files.
// Source: https://stackoverflow.com/a/228757/15507414
#ifndef _TYPES_H
#define _TYPES_H
// only define stuff when file hasn't been included yet

typedef struct
{
    int x;
    int y;
} Vec2;

typedef struct
{
    bool **cells;
    Vec2 screenSize;
    Vec2 playerPos;
} BoardState;

#endif