#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdbool.h>
#include "../types.h"

/* Problem: get non-blocking keyboard input
potential source?: https://gamedev.stackexchange.com/questions/146256/how-do-i-get-getchar-to-not-block-the-input#comment258193_146256

the below ones weren't used, the solution was made in ansi_term.h, where i
made stdin non-blocking.
source: https://stackoverflow.com/a/30548692/15507414

getchar() now return -1 if there's no input
source: https://www.quora.com/What-is-return-type-of-getchar-fgetc-and-getc-in-C
*/
// Source: https://stackoverflow.com/a/448982/15507414
int kbhit()
{
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv) > 0;
}

int getch()
{
    int r;
    unsigned char c;
    if ((r = read(0, &c, sizeof(c))) < 0)
    {
        return r;
    }
    else
    {
        return c;
    }
}

typedef enum
{
    InputNormal = 0,
    InputUp,
    InputDown,
    InputRight,
    InputLeft,
} InputType;

typedef struct
{
    InputType type;
    char normalKey;
} Input;

typedef struct
{
    Input *inputs;
    size_t len;
} InputList;

bool parseInputBytes(const char *bytes, const size_t bytesLength, InputList **outList)
{
    bool searchingEscape = false;
    bool foundOpenSquareBracket = false;
    for (size_t i = 0; i < bytesLength; i++)
    {
        if (bytes[i] == '\e')
        {
            searchingEscape = true;
        }
        if (searchingEscape && bytes[i] == '[')
        {
            foundOpenSquareBracket = true;
        }
    }
}

bool handleInput(input)
{
}

bool takeInputs(BoardState *state, bool allowEdit)
{
}
