

#ifndef _ANSI_TERM_H
#define _ANSI_TERM_H

void moveCursorHome();
void activateAlternativeBuffer();
void disableAlternativeBuffer();
void showCursor();
void hideCursor();

void flushCommands();

void enterNonCanonicalMode();
void exitNonCanonicalMode();

#endif