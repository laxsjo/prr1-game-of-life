#include <sys/ioctl.h>
#include <stdio.h>

    int getTerminalSize(){
        struct winsize termSize;
        ioctl(0, TIOCGWINSZ, &termSize);

        printf("Terminal size:\n");
        printf ("Columns (Y-axis): %d\n", termSize.ws_row);
        printf ("Rows (X-axis): %d\n\n", termSize.ws_col);
    }
