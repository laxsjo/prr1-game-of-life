#include "types.h"
#include "rasmus/rasmus_example.h"
#include <stdio.h>

int main()
{
    Vec2 test = {-5, 2};

    printf("Rasmus testing 123 %i %u\n", test.x, test.y);

    doStuffRasmus();

    return 0;
}