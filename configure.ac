AC_INIT([csgo_prs], [0.0.0], [@bugreport@], [csgo_prs])
AC_CONFIG_HEADERS(config.h)
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([build-aux/m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects no-dist-gzip dist-bzip2])
 
AC_SUBST(PACKAGE_AUTHOR, ["celestian"])
AC_SUBST(PACKAGE_DESCRIPTION, ["CS:GO Demo Parser"])
AC_SUBST(PACKAGE_HOMEPAGE, [""])
AC_SUBST(PACKAGE_MONTH, [$(LANG=C date '+%B')])
AC_SUBST(PACKAGE_YEAR, [$(LANG=C date '+%Y')])

# Debug
AC_ARG_ENABLE(debug,
AS_HELP_STRING([--enable-debug],
               [enable debugging, default: no]),
[case "${enableval}" in
             yes) debug=true ;;
             no)  debug=false ;;
             *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],
[debug=false])

AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")


# Relative proto_path
AC_ARG_ENABLE(relprotopath,
AS_HELP_STRING([--enable-relprotopath],
               [enable relative proto path, default: no]),
[case "${enableval}" in
             yes) relprotopath=true ;;
             no)  relprotopath=false ;;
             *)   AC_MSG_ERROR([bad value ${enableval} for --enable-relprotopath]) ;;
esac],
[relprotopath=false])

AM_CONDITIONAL(RELPROTOPATH, test x"$relprotopath" = x"true")


# ProtoBuf compiler.
# First, specify with --with-protoc=/path/of/protoc.
# Or, specify with env variable PROTOC.
# If neither of the above, find it in the path.
#AC_MSG_CHECKING([for ProtoBuf compiler protoc])
AC_ARG_WITH([protoc],
    [AS_HELP_STRING([--with-protoc=/path/of/protoc],
        [Location of the protocol buffers compiler protoc. Defaults to looking on path.])],
    [PROTOC="$withval"],
    [ AS_IF([test "x${PROTOC}" == "x"],
        [AC_PATH_PROG([PROTOC], [protoc], [no])])
    ]
)
#AC_MSG_RESULT([${PROTOC}])
AS_IF([test "${PROTOC}" == "no"], [AC_MSG_ERROR([ProtoBuf compiler "protoc" not found.])])

# Checks for programs.
AC_PROG_CXX

AC_CHECK_PROG([PROTOC], [protoc], [protoc])
AS_IF([test "x${PROTOC}" == "x"],
    [AC_MSG_ERROR([ProtoBuf compiler "protoc" not found.])])

# Checks for libraries.
AX_PTHREAD
PKG_CHECK_MODULES(PROTOBUF, protobuf >= 2.5.0)

# Checks for header files.
AC_STDC_HEADERS

# Checks for typedefs, structures, and compiler characteristics.
AX_CHECK_COMPILE_FLAG([-std=c11], [
  CFLAGS+=" -std=c11"
], [
  echo "C compiler cannot compile C11 code"
  exit -1
])

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
