#include "../types.h"

#ifndef _INPUT_H
#define _INPUT_H

typedef enum
{
    InputNormal = 0,
    InputUp,
    InputDown,
    InputRight,
    InputLeft,
} KeyType;

typedef struct
{
    KeyType type;
    char normalKey;
} Input;

typedef struct
{
    Input *inputs;
    size_t len;
} InputList;

void freeInputList(InputList list);

/*
Convert a raw array of input bytes into a `InputList`.
*/
bool parseInputBytes(const char *bytes, const size_t bytesLength, InputList *outList);

#endif