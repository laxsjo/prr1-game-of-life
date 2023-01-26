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