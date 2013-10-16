AC_PREREQ(2.62)
AC_INIT(lua-fastcgi, 0.1.1, viallard@syscom.ch)
AM_INIT_AUTOMAKE([foreign])

sinclude(m4/ax_cflags_gcc_option.m4)

# workaround autoconf setting default flags which we don't want
test ".$CFLAGS" = "." && CFLAGS=" "

# programs needed to build/install
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_RANLIB

# libs needed
PKG_CHECK_MODULES([LUA], [lua >= 5.1],,
                  [PKG_CHECK_MODULES([LUA], [lua5.1 >= 5.1])])
AC_SUBST(LUA_CFLAGS)
AC_SUBST(LUA_LIBS)

# config options
AC_ARG_ENABLE(debug,
        [  --enable-debug  compile lua-fastcgi with debug flags])

# pimp CFLAGS
if test "x$GCC" = "xyes"; then
   # gcc specific options
   CFLAGS="$CFLAGS -Wall -Wextra"
   AX_CFLAGS_GCC_OPTION(-Wfloat-equal)
   AX_CFLAGS_GCC_OPTION(-Wundef)
   AX_CFLAGS_GCC_OPTION(-Wshadow)
   AX_CFLAGS_GCC_OPTION(-Wpointer-arith)
#   AX_CFLAGS_GCC_OPTION(-Wcast-align)
   AX_CFLAGS_GCC_OPTION(-Wstrict-prototypes)
   AX_CFLAGS_GCC_OPTION(-Wstrict-overflow=5)
   AX_CFLAGS_GCC_OPTION(-Wwrite-strings)
   AX_CFLAGS_GCC_OPTION(-Waggregate-return)
   AX_CFLAGS_GCC_OPTION(-Wcast-qual)
   AX_CFLAGS_GCC_OPTION(-Wswitch-default)
#   AX_CFLAGS_GCC_OPTION(-Wswitch-enum)
   AX_CFLAGS_GCC_OPTION(-Wconversion)
   AX_CFLAGS_GCC_OPTION(-Wunreachable-code)
   AX_CFLAGS_GCC_OPTION(-Wformat=2)
   AX_CFLAGS_GCC_OPTION(-Wformat-y2k)
   AX_CFLAGS_GCC_OPTION(-Wno-format-extra-args)
   AX_CFLAGS_GCC_OPTION(-Wno-format-zero-length)
   AX_CFLAGS_GCC_OPTION(-Wformat-nonliteral)
   AX_CFLAGS_GCC_OPTION(-Wformat-security)
fi

if test "x$enable_debug" = "xyes"; then
   AC_MSG_RESULT(> enable debug)
   CFLAGS="$CFLAGS -g -DDEBUG"
fi

# the generated files
AC_CONFIG_FILES([
Makefile
src/Makefile
])

AC_OUTPUT
