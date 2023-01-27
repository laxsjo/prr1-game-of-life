#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
// #include <termios.h>
#include <fcntl.h>
// #include <iostream>
#include "general.h"
#include "ansi_term.h"
#include "game_logic.h"

volatile sig_atomic_t initCalled = false;
volatile sig_atomic_t fcntl_default;

void cleanUp();

void exitSignal(int sig_num)
{
    // disableAlternativeBuffer();
    // exitNonCanonicalMode();
    cleanUp();
    // why 128: https://stackoverflow.com/a/57944209/15507414
    exit(128 + sig_num);
}

/*
Problem: I needed signal handlers to clear a bunch of flags and stuff to reset
the terminal, but there's a bunch of thread funkyness when inside a signal
handler function.
I ended up converting the ansi_term functions to not use printf, but to instead
use write, since printf isn't signal safe.
I also changed the globals to be atomic types.

source: https://stackoverflow.com/a/16891799/15507414
*/

void initBoardDisplay()
{
    /// source: https://stackoverflow.com/questions/554138/catching-segfaults-in-c
    signal(SIGINT, exitSignal);
    signal(SIGILL, exitSignal);
    signal(SIGABRT, exitSignal);
    signal(SIGFPE, exitSignal);
    signal(SIGSEGV, exitSignal);
    signal(SIGTERM, exitSignal);

    fcntl_default = fcntl(0, F_GETFL);
    // non blocking source: https://gamedev.stackexchange.com/a/146263
    // the main source: https://stackoverflow.com/a/30548692/15507414
    fcntl(0, F_SETFL, fcntl_default | O_NONBLOCK);

    initCalled = true;
    hideCursor();
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