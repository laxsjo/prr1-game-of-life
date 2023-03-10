#include <sys/ioctl.h>
#include <stdio.h>
#include "../types.h"

Vec2 getTerminalSize()
{
    //get the current size of the terminal and let that be the return value
    struct winsize termSize;
    ioctl(0, TIOCGWINSZ, &termSize);

    Vec2 size;

    size.y = termSize.ws_row;
    size.x = termSize.ws_col / 2;

    return (Vec2){size.x, size.y};
}
