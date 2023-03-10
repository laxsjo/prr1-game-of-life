#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdbool.h>
#include "../types.h"
#include "input.h"

void freeInputList(InputList list)
{
    free(list.inputs);
}

/* Problem: get non-blocking keyboard input
potential source?: https://gamedev.stackexchange.com/questions/146256/how-do-i-get-getchar-to-not-block-the-input#comment258193_146256

the below ones weren't used, the solution was made in ansi_term.h, where i
made stdin non-blocking.
source: https://stackoverflow.com/a/30548692/15507414

getchar() now return -1 if there's no input
source: https://www.quora.com/What-is-return-type-of-getchar-fgetc-and-getc-in-C
*/
// // Source: https://stackoverflow.com/a/448982/15507414

bool parseInputBytes(const char *bytes, const size_t bytesLength, InputList *outList)
{
    /* Potential memory optimization: this potentially overestimates length,
    if input bytes included multi byte inputs.
    */
    Input *inputs = malloc(sizeof(Input) * bytesLength);
    size_t listIndex = 0;

    bool searchingEscape = false;
    bool foundOpenSquareBracket = false;
    for (size_t i = 0; i < bytesLength; i++)
    {
        if (bytes[i] == '\e' && i + 2 < bytesLength)
        {
            searchingEscape = true;
            char second = bytes[i + 1];
            if (second != '[')
            {
                inputs[listIndex++] = (Input){InputNormal, '\e'};
                // inputs[listIndex++] = (Input){InputNormal, second};
                continue;
            }
            // i++;

            char third = bytes[i + 2];
            switch (third)
            {
            case 'A':
                inputs[listIndex++] = (Input){InputUp, 0};
                break;
            case 'B':
                inputs[listIndex++] = (Input){InputDown, 0};
                break;
            case 'C':
                inputs[listIndex++] = (Input){InputRight, 0};
                break;
            case 'D':
                inputs[listIndex++] = (Input){InputLeft, 0};
                break;
            default:
                inputs[listIndex++] = (Input){InputNormal, '\e'};
                // inputs[listIndex++] = (Input){InputNormal, second};
                // inputs[listIndex++] = (Input){InputNormal, third};
                continue;
            }
            i += 2;
            continue;
        }

        inputs[listIndex++] = (Input){InputNormal, bytes[i]};
    }

    outList->len = listIndex;

    outList->inputs = inputs;
}
