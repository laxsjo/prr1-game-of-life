#include <string.h>
#include "../types.h"

StrSlice strSliceFromStr(char *str)
{
    size_t len = strlen(str);

    StrSlice slice = {str, len};

    return slice;
}

StrSlice strGetSlice(char *str, size_t start, size_t len)
{
    StrSlice slice = {str + start, len};

    return slice;
}

char *strSliceToStr(const StrSlice slice)
{
    char *out = malloc(slice.len + 1);
    memcpy(out, slice.str, slice.len);

    return out;
}

/* Returns the amount of characters in str that are apart of charSet. */
size_t strSliceCountCharOccurrences(const StrSlice *restrict str, const char *charSet)
{
    size_t setLen = strlen(charSet);
    size_t count = 0;
    for (size_t i = 0; i < str->len; i++)
    {
        for (size_t j = 0; j < setLen; j++)
        {
            if (str->str[i] == charSet[j])
            {
                count++;
            }
        }
    }

    return count;
}