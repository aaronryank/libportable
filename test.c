#include "portable.h"

int main(void)
{
    printf("%d\n", PORTABLY(detect,tty,stdout));
}
