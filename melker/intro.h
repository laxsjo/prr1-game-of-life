#include <stdbool.h>

void runIntro();
void speakGen(int dialogueLength, char *message, bool isShocked);
void enableRawMode();
void disableRawMode();
void die(const char *s);
void printFace(bool isShocked);