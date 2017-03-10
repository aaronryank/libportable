/*  porable.c | libportable's base functions
 *  Copyright (C) 2017 Aaron Ryan Klingler
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "portable.h"

char *
strlower(char *t)
{
    int i;
    for (i = 0; t[i]; i++)
        t[i] = tolower(t[i]);

    return t;
}

// avoid GCC telling us we're returning the address of a local variable
char *
strlower_handlerfunc(char *t)
{
    char *s = malloc(strlen(t));    // can't free this, so allocate the minimum amount.
    memset(s, 0, 50);
    memcpy(s, t, strlen(t));

    return strlower(s);
}

#define LOWERCASE3(x) strlower_handlerfunc(x)
#define LOWERCASE2(x) LOWERCASE3(#x)
#define LOWERCASE(x)  LOWERCASE2(x)

char *
get_system_name(void)
{
    if (SYSTEM == SYS_UNDEFINED)
        return "";
    else
        return LOWERCASE(SYSTEM);
}