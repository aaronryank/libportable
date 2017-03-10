/*  PORTABLY(cursor, home) | home the cursor (put it at 0x0y)
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

#define POSIX__home_cursor()    POSIX__set_cursor(0, 0)
#define WINDOWS__home_cursor()  WINDOWS__set_cursor(0, 0)