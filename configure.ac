#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE(libitl-gobject.la, 1.0)
AC_CONFIG_SRCDIR([itl-gobject.c])
#AC_CONFIG_HEADERS([config.h])

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

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
