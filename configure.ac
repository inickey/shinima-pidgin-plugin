AC_PREREQ([2.50])
AC_INIT([shinima-pidgin-plugin], [0.1])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([src/shinima-pidgin-plugin.c])
AC_ARG_VAR(PLUGINDIR, [the installation directory for the plugin])
AC_PROG_CC
AM_PROG_CC_C_O
CFLAGS="-g -Wall -O2"
AC_DISABLE_STATIC
AC_PROG_LIBTOOL
LIBTOOL="$LIBTOOL --silent"
AC_PROG_INSTALL
PKG_PROG_PKG_CONFIG

# Checking for libs
PKG_CHECK_MODULES(GLIB, glib-2.0)
PKG_CHECK_MODULES(SOUP, libsoup-2.4)
PKG_CHECK_MODULES(PIDGIN, pidgin purple)

AC_SUBST(GLIB_CFLAGS)
AC_SUBST(GLIB_LIBS)
AC_SUBST(SOUP_CFLAGS)
AC_SUBST(SOUP_LIBS)
AC_SUBST(PIDGIN_CFLAGS)
AC_SUBST(PIDGIN_LIBS)

if test "$PLUGINDIR" = ""
then
	if test "$prefix" = "NONE"
	then
		PLUGINDIR="`pkg-config --variable=libdir pidgin`/pidgin"
	else
		PLUGINDIR="$prefix/lib/pidgin"
	fi
fi

AC_CONFIG_FILES([
	Makefile
	src/Makefile
])
AC_OUTPUT
