#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/*
Dynamically growing list
source: https://stackoverflow.com/a/46351960/15507414
*/

// these fancy generating macros just seem to cause issues with intellisense and compilation...
// #define defineListType(type) \
//     typedef struct           \
//     {                        \
//         size_t len;          \
//         type array[];        \
//     } list_##type##_t;       \
//     int push_back_##type(list_##type##_t **list, type value);

// #define defineListFunction(type)                                                             \
//     int push_back_##type(list_##type##_t **list, type value)                                 \
//     {                                                                                        \
//         size_t x = *list ? list[0]->len : 0, y = x + 1;                                      \
//                                                                                              \
//         if ((x & y) == 0)                                                                    \
//         {                                                                                    \
//             void *temp = realloc(*list, sizeof **list + (x + y) * sizeof list[0]->array[0]); \
//             if (!temp)                                                                       \
//             {                                                                                \
//                 return 1;                                                                    \
//             }                                                                                \
//             *list = temp;                                                                    \
//         }                                                                                    \
//                                                                                              \
//         list[0]->array[x] = value;                                                           \
//         list[0]->len = y;                                                                    \
//         return 0;                                                                            \
//     }
// defineListType(char)

typedef struct
{
    size_t len;
    char array[];
} list_char_t;
int push_back_char(list_char_t **list, char value);
list_char_t *new_char_list();

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

// defineListType(char);

// typedef struct
// {
//     size_t len;
//     char array[];
// } CharList;

// int push_back(CharList **list, int value)
// {
//     size_t x = *list ? list[0]->len : 0, y = x + 1;

//     if ((x & y) == 0)
//     {
//         void *temp = realloc(*list, sizeof **list + (x + y) * sizeof list[0]->array[0]);
//         if (!temp)
//         {
//             return 1;
//         }
//         *list = temp;
//     }

//     list[0]->array[x] = value;
//     list[0]->len = y;
//     return 0;
// }

#endif