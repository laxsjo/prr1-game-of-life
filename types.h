#include <stdbool.h>
#include <stdlib.h>

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

typedef struct
{
    u_int8_t r;
    u_int8_t g;
    u_int8_t b;
} Rgb;

typedef struct
{
    char *str;
    size_t len;
} StrSlice;

#endif