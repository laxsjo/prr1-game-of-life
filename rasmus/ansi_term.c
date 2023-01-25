#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

#include "../types.h"
#include "ansi_term.h"
#include "general.h"

void moveCursorHome()
{
    printf("\x1b[H");
}

void activateAlternativeBuffer()
{
    printf("\x1b[?1049h");
}

void disableAlternativeBuffer()
{
    printf("\x1b[?1049l");
}

void showCursor()
{
    printf("\x1b[?25h");
}
void hideCursor()
{
    printf("\x1b[?25l");
}

void flushCommands()
{
    fflush(stdout);
}

void resetFormat()
{
    printf("\x1b[0m");
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

    printf("%u", settings.c_lflag);

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
    printf("%i\n", fd);

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