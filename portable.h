/*  porable.h | libportable's header
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

#ifndef _PORTABLE_H
#define _PORTABLE_H

/****************
 DETERMINE SYSTEM
 ****************/

enum {
    SYS_UNDEFINED,
    WINDOWS,
    UNIX,
    APPLE,
    //SOLARIS is a true unix system, according to http://stackoverflow.com/a/20136190/6850771.
} __major_system_types;

/* all possible Windows predefined macros */
#if defined(WIN32)       || \
    defined(_WIN32)      || \
    defined(__WIN32)     || \
    defined(__WIN32__)   || \
    defined(__MINGW32__) || \
    defined(WINNT)       || \
    defined(__WINNT)     || \
    defined(__WINNT__)   || \
    defined(__CYGWIN__)

# define SYSTEM WINDOWS
# define SYSTEM_WINDOWS

/* all true UNIX systems */
#elif defined(unix)     || \
      defined(__unix__) || \
      defined(__unix)   || \
      defined(__linux)  || \
      defined(__linux__)|| \
      defined(__sun)    || \
      defined(__SVR4)

# define SYSTEM UNIX
# define SYSTEM_UNIX

/* Apple defines both. */
#elif defined(__APPLE__) && defined(__MACH__)

# define SYSTEM APPLE
# define SYSTEM_APPLE

#else
# define SYSTEM SYS_UNDEFINED
#endif

/*********************
 SYSTEM-SPECIFIC STUFF
 *********************/

#ifdef SYSTEM_WINDOWS
# include <windows.h>
# include <tchar.h>

# ifndef __CYGWIN__
#  include <conio.h>
# endif

# define PERR(bSuccess, api) {if(!(bSuccess)) printf("%s: Error %d from %s on line %d\n", __FILE__, (int) GetLastError(), api, (int) __LINE__);}
#else
# define PERR(success, api) {if(!(success)) printf("%s: Error in %s on line %d\n", __FILE__, api, (int) __LINE__);}
#endif

#ifdef SYSTEM_UNIX
# include <unistd.h>
# include <termios.h>
# include <signal.h>
#endif

/****************************
 DETERMINE IF POSIX-COMPLIANT
 ****************************/

#undef POSIX

#if defined(__ECOS) ||                                                 \
    defined(_AIX) ||                                                   \
    defined(_hpux) || defined(hpux) || defined(__hpux) ||              \
    defined(sgi) || defined(__sgi) ||                                  \
    defined(__linux__) || defined(linux) || defined(__linux) ||        \
    defined(__APPLE__) || defined(__MACH__) ||                         \
    defined(sun) || defined(__sun) ||                                  \
    defined(__osf__) || defined(__osf) ||                              \
    defined(sco) || defined(_UNIXWARE7) ||                             \
    defined(__QNXNTO__) ||                                             \
    defined(__INTEGRITY) ||                                            \
    defined(__ANRDOID__) ||                                            \
    defined(__BEOS__) ||                                               \
    defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined (__bsdi__) || defined (__DragonFly__) ||\
    defined(__minix) ||                                                \
    defined(mpeix) || defined(__mpexl) ||                              \
    defined(__NetBSD__) ||                                             \
    defined(__nucleus__) ||                                            \
    defined(__SYLLABLE__) ||                                           \
    defined(__VXWORKS__) || defined(__vxworks) ||                      \
    defined(M_XENIX) ||                                                \
    defined(__EMX__) ||                                                \
    defined(__MVS__) || defined(__HOS_MVS__) || defined(__TOS_MVS__) ||\
    defined(__CYGWIN__)

# define POSIX
#endif

/***********************
 CALL PORTABLE FUNCTIONS
 ***********************/

#define ___P(x, y) x ## y
#define __P(x, y) ___P(x, y)

#ifdef POSIX
# define EXTERN_PORTABLE(return_type, family, function) extern return_type __P(POSIX##__, __P(__P(function, _), family))
# define PORTABLY(family, function, ...)  __P(POSIX##__, __P(__P(function, _), family))  (__VA_ARGS__)
#else
# define EXTERN_PORTABLE(return_type, family, function) extern return_type __P(__P(SYSTEM, __), __P(__P(function, _), family))
# define PORTABLY(family, function, ...)  __P(__P(SYSTEM, __), __P(__P(function, _), family))  (__VA_ARGS__)
#endif

/*******
 EXTERNS
 *******/

EXTERN_PORTABLE(int, cursor, set)     (int, int);
EXTERN_PORTABLE(void, screen, clear)  (void);
EXTERN_PORTABLE(int, cursor, home)    (void);
EXTERN_PORTABLE(int, text, color)     (int);
EXTERN_PORTABLE(int, system, execute) (const char *);

// portability info
extern char *get_system_name(void);

/*******************
 COMPILER TYPE     *
 PRAGMA ONCE SUPPORT
 *******************/

enum {
    CC_UNDEFINED,
    CC_ORACLE,
    CC_MSVC,
    CC_CLANG,
    CC_COMEAU,
    CC_CPPBUILDER,
    CC_DIGITALMARS,
    CC_GCC,
    CC_HP,
    CC_IBM,
    CC_INTEL,
    CC_PELLES,
    CC_ARM,
    CC_IAR,
    CC_PORTLAND,
    CC_UNKNOWN
} __compiler_types;

#undef _pragma_once_support
#undef COMPILER

#if defined(__SUNPRO_C) || defined(__SUNPRO_CC) // Oracle Developer Studio C/C++ 
# define COMPILER CC_ORACLE
# if (__SUNPRO_C>=0x5140) || (__SUNPRO_CC>=0x5140)    // (12.5 or later)
#  define _pragma_once_support 1
# endif
#elif defined(_MSC_VER)         	// MSVC
# define COMPILER CC_MSVC
# if (_MSC_VER>=1020)
#  define _pragma_once_support 1
# endif
#elif defined(__clang__)		// clang
# define COMPILER CC_CLANG
# define _pragma_once_support 1
#elif defined(__COMO__)			// comeau
# define COMPILER CC_COMEAU
# define _pragma_once_support 1
#elif defined(__CODEGEARC__)            // C++Builder (XE3 or greater)
# define COMPILER CC_CPPBUILDER
# if (__CODEGEARC__ >=650)
#  define _pragma_once_support 1
# endif
#elif defined(__DMC__)			// Digital Mars
# define COMPILER CC_DIGITALMARS
# define _pragma_once_support 1
#elif defined(__GNUC__)                 // GCC
# define COMPILER CC_GCC
# if ((__GNUC__ > 3)||(defined(__GNUC_MINOR__)&&(__GNUC__ == 3)&&(__GNUC_MINOR__ >= 4)))    // GCC
#  define _pragma_once_support 1
# endif
#elif defined(__HP_aCC)                 // HP aC++ (A.06.12)
# define COMPILER CC_HP
# if (__HP_aCC >=61200)
#  define _pragma_once_support 1
# endif
#elif defined(__xlC__)                  // IBM
# define COMPILER CC_IBM
# if ((__xlC__ >1301)||((__xlC__ ==1301)&&(__xlC_ver__ >0100)))
#  define _pragma_once_support 1
# endif
#elif defined(__INTEL_COMPILER)||defined(__ICC)||defined(__ECC)||defined(__ICL)      // Intel
# define COMPILER CC_INTEL
# define _pragma_once_support 1
#elif defined(__POCC__)			// Pelles C
# define COMPILER CC_PELLES
# define _pragma_once_support 1
#elif defined(__CC_ARM)			// ARM compiler
# define COMPILER CC_ARM
# define _pragma_once_support 1
#elif defined(__IAR_SYSTEMS_ICC__)	// IAR C/C++
# define COMPILER CC_IAR
# define _pragma_once_support 1
#elif defined(__PGI)			// Portland Group C/C++
# define COMPILER CC_PORTLAND
# define _pragma_once_support 0
#else				        // Unknown
# define COMPILER CC_UNKNOWN
# define _pragma_once_support 0
#endif

#endif // portable.h