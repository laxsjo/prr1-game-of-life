#include "../types.h"

#ifndef _ANSI_TERM_H
#define _ANSI_TERM_H

#define FG_COLOR_BLACK 30
#define FG_COLOR_RED 31
#define FG_COLOR_GREEN 32
#define FG_COLOR_YELLOW 33
#define FG_COLOR_BLUE 34
#define FG_COLOR_MAGENTA 35
#define FG_COLOR_CYAN 36
#define FG_COLOR_WHITE 37
#define FG_COLOR_DEFAULT 39

#define BG_COLOR_BLACK 40
#define BG_COLOR_RED 41
#define BG_COLOR_GREEN 42
#define BG_COLOR_YELLOW 43
#define BG_COLOR_BLUE 44
#define BG_COLOR_MAGENTA 45
#define BG_COLOR_CYAN 46
#define BG_COLOR_WHITE 47
#define BG_COLOR_DEFAULT 49

#define SEQ_MOVE_CURSOR_HOME "\x1b[H"
#define SEQ_ACTIVATE_ALTERNATIVE_BUFFER "\x1b[?1049h"
#define SEQ_DISABLE_ALTERNATIVE_BUFFER "\x1b[?1049l"
#define SEQ_SHOW_CURSOR "\x1b[?25h"
#define SEQ_HIDE_CURSOR "\x1b[?25l"
#define SEQ_RESET_FORMAT "\x1b[0m"

void moveCursorHome();
void activateAlternativeBuffer();
void disableAlternativeBuffer();
void showCursor();
void hideCursor();

void resetFormat();
void setFormatColor(u_int8_t color);
void setFormatFgRgb(Rgb color);
void setFormatBgRgb(Rgb color);

void moveCursorHomePrintf();
void showCursorPrintf();
void hideCursorPrintf();
void resetFormatPrintf();

char *getSetFormatBgRgb(Rgb color);
char *getSetFormatFgRgb(Rgb color);
char *getSetFormatColor(u_int8_t color);

void flushCommands();

void enterNonCanonicalMode();
void exitNonCanonicalMode();

#endif