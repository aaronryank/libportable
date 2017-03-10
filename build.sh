cc pfunc/*.c -c -Wall -Wextra -Werror
cc portability.c -c -Wall -Wextra -Werror
ar ruv portable.a *.o
ranlib portable.a