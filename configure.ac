#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(replace, 1.0)
AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE(replace, 1.0)

case "$target" in
  *-*-darwin*)
    PLATFORM=_MACOS
    ;;

  *-*-linux*)
    PLATFORM=_LINUX
    ;;

  *-*-cygwin)
    PLATFORM=_LINUX
    ;;

  *)
    AC_MSG_ERROR(unsupported platform ${target})
    ;;
esac

AC_SUBST(PLATFORM)

AC_CONFIG_MACRO_DIRS([m4])

# Boost dep
AX_BOOST_BASE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LIBTOOL

AC_OUTPUT([Makefile])
