# prr1-game-of-life
This was a group assignment for school, where we choose to create a Conway's Game of Life simulator in the terminal

## For anyone looking through this repository (like someone named Jonas Björk as an example ;) )
This project mainly consists of two folders, `rasmus/` and `melker/`. One for
each of us. These contain the code that the corresponding person (roughly) worked
on. We avoided making changes in the other persons folder to avoid our changes
colliding and making git sad.

There was also the `types.h` (and `types.c`) file which didn't really belong to
anyone, so it is therefore placed in the root.

We also each got a `<name>_test.c` file, which acted like the `main.c` file
while debugging, so that we were free to test things, without editing `main.c`
and causing collisions making git sad again.

The final binary (`gol`) was compiled using the small `build.sh` shell script we
wrote to make compiling easier.

There was also a `build_test.sh` script to build our corresponding test programs
(`melker_test.c` and `rasmus_test.c`), but you don't need to worry about this.
