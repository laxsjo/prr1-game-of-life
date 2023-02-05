#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

#include "../types.h"
#include "ansi_term.h"
#include "general.h"

void moveCursorHome()
{
    // printf("\x1b[H");
    //
    write(0, SEQ_MOVE_CURSOR_HOME, sizeof(SEQ_MOVE_CURSOR_HOME) - 1);
}
void moveCursorHomePrintf()
{
    printf(SEQ_MOVE_CURSOR_HOME);
}

void activateAlternativeBuffer()
{
    // printf("\x1b[?1049h");
    write(0, SEQ_ACTIVATE_ALTERNATIVE_BUFFER, sizeof(SEQ_ACTIVATE_ALTERNATIVE_BUFFER) - 1);
}

void disableAlternativeBuffer()
{
    // why I use write: https://stackoverflow.com/a/16891799/15507414
    // also: https://docs.oracle.com/cd/E19455-01/806-5257/gen-26/index.html
    // printf("\x1b[?1049l");
    write(0, SEQ_DISABLE_ALTERNATIVE_BUFFER, sizeof(SEQ_DISABLE_ALTERNATIVE_BUFFER) - 1);
}

void showCursor()
{
    // printf("\x1b[?25h");
    write(0, SEQ_SHOW_CURSOR, sizeof(SEQ_SHOW_CURSOR) - 1);
}
void showCursorPrintf()
{
    printf(SEQ_SHOW_CURSOR);
}
void hideCursorPrintf()
{
    printf(SEQ_HIDE_CURSOR);
}
void hideCursor()
{
    // printf("\x1b[?25l");
    write(0, SEQ_HIDE_CURSOR, sizeof(SEQ_HIDE_CURSOR) - 1);
}

void flushCommands()
{
    fflush(0);
}

void resetFormatPrintf()
{
    printf(SEQ_RESET_FORMAT);
}
void resetFormat()
{
    // printf("\x1b[0m");
    write(0, SEQ_RESET_FORMAT, sizeof(SEQ_RESET_FORMAT) - 1);
}

void setFormatColor(u_int8_t color)
{
    printf("\x1b[%um", color);
}

void setFormatFgRgb(Rgb color)
{
    printf("\x1b[38;2;%u;%u;%um", color.r, color.g, color.b);
}

void setFormatBgRgb(Rgb color)
{
    printf("\x1b[48;2;%u;%u;%um", color.r, color.g, color.b);
}

int getTerminalFd()
{
    // source: https://stackoverflow.com/a/35923674/15507414
    if (isatty(fileno(stdin)))
    {
        return fileno(stdin);
    }
    else if (isatty(fileno(stdout)))
    {
        return fileno(stdout);
    }
    else if (isatty(fileno(stderr)))
    {
        return fileno(stderr);
    }
    else
    {
        // no terminal found :(
        return -1;
    }
}

void setTerminalFlags(int flags)
{
    // source: https://www.gnu.org/software/libc/manual/html_node/Setting-Modes.html
    struct termios settings;
    int result;

    int fd = getTerminalFd();
    if (fd == -1)
    {
        panic("terminal file descriptor not found :(");
    }

    result = tcgetattr(fd, &settings);
    if (result < 0)
    {
        panic("error in tcgetattr");
    }

    // printf("%u", settings.c_lflag);

    // why i choose c_lflag: https://www.gnu.org/software/libc/manual/html_node/Local-Modes.html
    settings.c_lflag |= flags;

    result = tcsetattr(fd, TCSANOW, &settings);
    if (result < 0)
    {
        panic("error in tcgetattr");
    }
}

void unsetTerminalFlags(int flags)
{
    // source: https://www.gnu.org/software/libc/manual/html_node/Setting-Modes.html
    struct termios settings;
    int result;

    int fd = getTerminalFd();
    if (fd == -1)
    {
        panic("terminal file descriptor not found :(\r\n");
    }
    // printf("%i\n", fd);

    result = tcgetattr(fd, &settings);
    if (result < 0)
    {
        panic("error in tcgetattr");
    }

    // why i choose c_lflag: https://www.gnu.org/software/libc/manual/html_node/Local-Modes.html
    settings.c_lflag &= ~flags;

    result = tcsetattr(fd, TCSANOW, &settings);
    if (result < 0)
    {
        panic("error in tcgetattr");
    }
}

void enterNonCanonicalMode()
{
    // source: https://www.gnu.org/software/libc/manual/html_node/Local-Modes.html
    unsetTerminalFlags(ICANON | ECHO);
}

void exitNonCanonicalMode()
{
    // source: https://www.gnu.org/software/libc/manual/html_node/Local-Modes.html
    setTerminalFlags(ICANON | ECHO);
}