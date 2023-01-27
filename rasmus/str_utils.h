#include "../types.h"

#ifndef _STR_UTILS_H
#define _STR_UTILS_H

StrSlice strSliceFromStr(char *str);

StrSlice strGetSlice(const char *str, size_t start, size_t len);

char *strSliceToStr(const StrSlice slice);

/* Returns the amount of characters in str that are apart of charSet. */
size_t strSliceCountCharOccurrences(const StrSlice *str, const char *charSet);

void freeStrList(char **strings, size_t len);

#endif