# libkc - Shared Keycloak/HTTP library

lib_LTLIBRARIES = libkc.la

libkc_la_SOURCES = \
	src/kc.c \
	src/kc_http.c \
	src/kc_keycloak.c \
	src/kc_webhook.c

libkc_la_CFLAGS = \
	$(AM_CFLAGS) \
	-I$(srcdir)/include

libkc_la_LIBADD = -lcurl -ljansson

# Install public headers
kcincludedir = $(includedir)/kc
kcinclude_HEADERS = \
	include/kc.h \
	include/kc_event.h \
	include/kc_log.h \
	include/kc_http.h \
	include/kc_keycloak.h \
	include/kc_webhook.h

# Also build a convenience static library for in-tree linking
noinst_LIBRARIES = libkc_static.a

libkc_static_a_SOURCES = $(libkc_la_SOURCES)
libkc_static_a_CFLAGS = $(libkc_la_CFLAGS)

EXTRA_DIST = README.md
