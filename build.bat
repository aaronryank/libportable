@echo off
gcc pfunc/*.c -c -Wall -Wextra -Werror
gcc portable.c -c -Wall -Wextra -Werror
ar cr libportable.a *.o
ranlib libportable.a
ERASE *.o