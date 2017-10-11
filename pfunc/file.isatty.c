#include "../portable.h"

#ifdef SYSTEM_WINDOWS

#include <io.h>
#include <stdio.h>

int WINDOWS__file_isatty(FILE *fd)
{
    return _isatty(fileno(fd));
}

#endif

#ifdef POSIX

#include <unistd.h>
#include <stdio.h>

int POSIX__file_isatty(FILE *fd)
{
    return isatty(fileno(fd));
}

#endif
