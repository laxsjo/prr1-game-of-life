#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// #include <termios.h>
#include <fcntl.h>
// #include <iostream>
#include "general.h"
#include "ansi_term.h"

static bool initCalled = false;
static int fcntl_default;

void initBoardDisplay()
{
    fcntl_default = fcntl(0, F_GETFL);
    // non blocking source: https://gamedev.stackexchange.com/a/146263
    // the main source: https://stackoverflow.com/a/30548692/15507414
    fcntl(0, F_SETFL, fcntl_default | O_NONBLOCK);

    initCalled = true;
    activateAlternativeBuffer();
    enterNonCanonicalMode();
}

void cleanUp()
{
    if (initCalled)
    {
        fcntl(0, F_SETFL, fcntl_default);

        disableAlternativeBuffer();
        exitNonCanonicalMode();
        initCalled = false;
    }
    resetFormat();
}

void _panic(const char *reason, const _LineInfo location)
{
    cleanUp();
    fprintf(stderr, "panicked at '%s',\n%s:%lu (in function '%s')\n", reason, location.file, location.line, location.func);
    exit(1);
}
