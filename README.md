The foci of this repository are the [thread.c](https://github.com/Valkryst/C_PThread/master/src/thread.c)
and [thread.h](https://github.com/Valkryst/C_PThread/master/src/thread.h)
files. They simplify the creation, destruction, and use of [POSIX Threads](https://en.wikipedia.org/wiki/Pthreads).

## Compiling

Add `thread.c` and `thread.h` to your project, and add
[-pthread flag](https://stackoverflow.com/a/2127819/13279616) to your compile
flags.

See the provided [Makefile](https://github.com/Valkryst/C_PThread/master/Makefile)
as a reference.

## Dependencies

For development purposes, `thread.c` depends on my
[C_Logging](https://github.com/Valkryst/C_Logging) library. By replacing all
calls to `printError` in `thread.c`, you can remove this dependency.