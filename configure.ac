#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
define([CURRENT], [1])
define([REV], [2])
define([AGE], [1])

AC_PREREQ([2.68])
AC_INIT([libitl-gobject], 0.2, [https://github.com/aelmahmoudy/libitl-gobject/issues])
AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_SRCDIR([src])
#AC_CONFIG_HEADERS([config.h])
LTVERSION=CURRENT:REV:AGE
AC_SUBST(LTVERSION)

AC_PROG_LIBTOOL
# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([itl], [getNorthQibla])

PKG_CHECK_MODULES(GOBJECT, gobject-2.0 >= 2.2.0)

GOBJECT_INTROSPECTION_CHECK([0.6.7])



# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile src/Makefile libitl-gobject.pc])
AC_OUTPUT
