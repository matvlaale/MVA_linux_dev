AC_INIT([Rhasher], [0.1], [])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_PROG_CC

AC_CHECK_LIB([rhash], [main], [],
	[AC_MSG_ERROR([Rhash library not found!])])

AC_ARG_WITH([readline],
  [AS_HELP_STRING([--with-readline], 
  [Fancy cli editing support])],
  [], 
  [with_readline=check])

LIBREADLINE=
AS_IF([test "x$with_readline" != xno],
  [AC_CHECK_LIB([readline], [main],
    [AC_SUBST([LIBREADLINE], ["-lreadline"])
     AC_DEFINE([USE_RL], [1],
               [Define if you have libreadline])
    ],
    [if test "x$with_readline" != xcheck; then
      AC_MSG_FAILURE(
        [--with-readline was given, but test for readline failed])
     fi
    ], -lrhash)])

# AM_CONDITIONAL([USE_LIBREADLINE], LIBREADLINE)
# AC_DEFINE([USE_RL], USE_READLINE, [libreadline])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
