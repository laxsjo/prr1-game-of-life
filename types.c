#include <time.h>
#include "types.h"

// defineListFunction(char);

int push_back_char(list_char_t **list, char value)
{
    size_t x = *list ? list[0]->len : 0, y = x + 1;

    if ((x & y) == 0)
    {
        void *temp = realloc(*list, sizeof **list + (x + y) * sizeof list[0]->array[0]);
        if (!temp)
        {
            return 1;
        }
        *list = temp;
    }

    list[0]->array[x] = value;
    list[0]->len = y;
    return 0;
}

list_char_t *new_char_list()
{
    // source: https://wiki.sei.cmu.edu/confluence/display/c/DCL38-C.+Use+the+correct+syntax+when+declaring+a+flexible+array+member
    list_char_t *list = (list_char_t *)malloc(sizeof(list_char_t) + sizeof(char) * 0); // maybe this 0 should be a 1? https://stackoverflow.com/questions/2022335/whats-the-point-of-malloc0
    list->len = 0;
    return list;
}

bool vec2Eq(Vec2 a, Vec2 b)
{
    return a.x == b.x && a.y == b.y;
}

#include <errno.h>

// source: https://stackoverflow.com/a/1157217/15507414
/* msleep(): Sleep for the requested number of milliseconds. */
int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do
    {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

void freeBoardCells(bool **cells, Vec2 size)
{
    for (size_t y = 0; y < size.y; y++)
    {
        free(cells[y]);
    }
    free(cells);
}

void freeBoardMessage(BoardState *state)
{
    free(state->message);
}