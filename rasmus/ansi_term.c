#include <stdio.h>
#include <termios.h>
#include <unistd.h>

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
        perror("terminal file descriptor not found :(\r\n");
        _exit(1);
    }

    result = tcgetattr(fd, &settings);
    if (result < 0)
    {
        perror("error in tcgetattr");
        _exit(1);
    }

    printf("%u", settings.c_lflag);

    // why i choose c_lflag: https://www.gnu.org/software/libc/manual/html_node/Local-Modes.html
    settings.c_lflag |= flags;

    result = tcsetattr(fd, TCSANOW, &settings);
    if (result < 0)
    {
        perror("error in tcgetattr");
        _exit(1);
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
        perror("terminal file descriptor not found :(\r\n");
        _exit(1);
    }
    printf("%i\n", fd);

    result = tcgetattr(fd, &settings);
    if (result < 0)
    {
        perror("error in tcgetattr");
        _exit(1);
    }

    // why i choose c_lflag: https://www.gnu.org/software/libc/manual/html_node/Local-Modes.html
    settings.c_lflag &= ~flags;

    result = tcsetattr(fd, TCSANOW, &settings);
    if (result < 0)
    {
        perror("error in tcgetattr");
        _exit(1);
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