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