gcc pfunc/*.c -c -Wall -Wextra -Werror
gcc portable.c -c -Wall -Wextra -Werror
ar ruv portable.a *.o
ranlib portable.a
rm *.o
