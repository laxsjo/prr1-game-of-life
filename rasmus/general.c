#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "general.h"
#include "ansi_term.h"

static bool initCalled = false;

void initBoardDisplay()
{
    initCalled = true;
    activateAlternativeBuffer();
    enterNonCanonicalMode();
}

void cleanUp()
{
    if (initCalled)
    {
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
