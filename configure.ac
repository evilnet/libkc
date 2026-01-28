AC_PREREQ([2.69])
AC_INIT([libkc], [0.1.0], [https://github.com/evilnet/libkc])
AC_CONFIG_SRCDIR([src/kc.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])

AM_INIT_AUTOMAKE([foreign subdir-objects -Wall -Werror])
AM_SILENT_RULES([yes])

# Use libtool for building static/shared library
LT_INIT

# Checks for programs
AM_PROG_AR
AC_PROG_CC

# Checks for header files
AC_CHECK_HEADERS([stdlib.h string.h stddef.h stdbool.h])

# Check for libcurl
AC_CHECK_HEADERS([curl/curl.h], [],
    [AC_MSG_ERROR([libcurl headers not found. Install libcurl4-openssl-dev.])])
AC_CHECK_LIB([curl], [curl_multi_init], [],
    [AC_MSG_ERROR([libcurl not found. Install libcurl4-openssl-dev.])])

# Check for jansson
AC_CHECK_HEADERS([jansson.h], [],
    [AC_MSG_ERROR([jansson headers not found. Install libjansson-dev.])])
AC_CHECK_LIB([jansson], [json_object], [],
    [AC_MSG_ERROR([libjansson not found. Install libjansson-dev.])])

# Check for OpenSSL (optional, for future JWKS/crypto)
AC_CHECK_HEADERS([openssl/ssl.h])
AC_CHECK_LIB([ssl], [SSL_new], [have_ssl=yes], [have_ssl=no])
AC_CHECK_LIB([crypto], [EVP_DigestInit], [have_crypto=yes], [have_crypto=no])

if test "x$have_ssl" = "xyes" -a "x$have_crypto" = "xyes"; then
    AC_DEFINE([HAVE_OPENSSL], [1], [Define if OpenSSL is available])
fi

# Compiler flags
AC_SUBST([AM_CFLAGS], ["-Wall -Wextra -Wno-unused-parameter"])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
