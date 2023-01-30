#include <sys/ioctl.h>
#include <stdio.h>
#include "../types.h"

    Vec2 getTerminalSize(){
        struct winsize termSize;
        ioctl(0, TIOCGWINSZ, &termSize);

        Vec2 size;

        size.y = termSize.ws_row;
        size.x = termSize.ws_col;

        return (Vec2){size.x, size.y};
    }
