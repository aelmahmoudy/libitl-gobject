
DISTCHECK_CONFIGURE_FLAGS = --enable-introspection

lib_LTLIBRARIES = libitl_gobject.la
libitl_gobject_la_CFLAGS = $(GOBJECT_CFLAGS) -I/usr/include/itl -DITL_GOBJECT_COMPILATION
libitl_gobject_la_LDFLAGS = -version-info $(LTVERSION)
libitl_gobject_la_LIBADD= $(GOBJECT_LIBS) -litl
libitl_gobject_la_SOURCES =	itl-gobject.c itl-gobject-enums.c
libitl_gobject_la_HEADERS =	itl-gobject.h itl-gobject-enums.h
libitl_gobject_ladir = $(includedir)/itl

BUILT_SOURCES=itl-gobject-enums.c itl-gobject-enums.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = @PACKAGE@.pc

CLEANFILES=itl-gobject-enums.c itl-gobject-enums.h

-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS = Itl-1.0.gir
INTROSPECTION_SCANNER_ARGS = --add-include-path=$(srcdir)
INTROSPECTION_COMPILER_ARGS = --includedir=$(srcdir)

if HAVE_INTROSPECTION
introspection_sources = $(libitl_gobject_la_SOURCES) $(libitl_gobject_la_HEADERS)

Itl-1.0.gir: libitl_gobject.la
Itl_1_0_gir_INCLUDES = GObject-2.0 GLib-2.0
Itl_1_0_gir_CFLAGS = $(INCLUDES) -I/usr/include/itl -DITL_GOBJECT_COMPILATION
Itl_1_0_gir_LIBS = libitl_gobject.la
Itl_1_0_gir_FILES = $(introspection_sources)

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(libdir)/girepository-1.0
typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES += $(gir_DATA) $(typelib_DATA)
endif

itl-gobject-enums.c: itl-gobject.h itl-gobject-enums.c.in
	glib-mkenums --template $@.in itl-gobject.h > $@

itl-gobject-enums.h: itl-gobject.h itl-gobject-enums.h.in
	glib-mkenums --template $@.in itl-gobject.h > $@
