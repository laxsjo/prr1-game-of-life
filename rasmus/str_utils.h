#include "../types.h"

#ifndef _STR_UTILS_H
#define _STR_UTILS_H

/*
Convert a string slice to a string.

unused
*/
StrSlice strSliceFromStr(char *str);

/*
Create a string slice of length from a string at a specific offset.
*/
StrSlice strGetSlice(const char *str, size_t start, size_t len);

/*
Copy a string slice to a c style string.

unused
*/
char *strSliceToStr(const StrSlice slice);

/* Returns the amount of characters in str that are apart of charSet. */
size_t strSliceCountCharOccurrences(const StrSlice *str, const char *charSet);

// unused
void freeStrList(char **strings, size_t len);

#endif