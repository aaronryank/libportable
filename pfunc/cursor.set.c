/*  PORTABLE(cursor, set, x, y) | set the cursor to {x, y}
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

#include "../portable.h"
#include <stdio.h>

int POSIX__set_cursor(int x, int y)
{
    printf("\e[%d;%dH", y, x);
    return 0; // always succeeds
}

int WINDOWS__set_cursor(int x, int y)
{
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
    COORD coordScreen = { x, y };

    int bSuccess = SetConsoleCursorPosition( hConsole, coordScreen );
    PERR( bSuccess, "SetConsoleCursorPosition" );
    return bSuccess;
}