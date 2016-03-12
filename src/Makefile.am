SHINIMA_PIDGIN_PLUGIN_CFLAGS = @GLIB_CFLAGS@ @SOUP_CFLAGS@ @PIDGIN_CFLAGS@
SHINIMA_PIDGIN_PLUGIN_LIBS = @GLIB_LIBS@ @SOUP_LIBS@ @PIDGIN_LIBS@

plugindir = @PLUGINDIR@
plugin_LTLIBRARIES = shinima-pidgin-plugin.la
shinima_pidgin_plugin_la_SOURCES = \
	shinima-pidgin-plugin.c \
	shinima-callbacks.c \
	shinima-link.c \
	shinima-message.c
shinima_pidgin_plugin_la_CFLAGS = $(SHINIMA_PIDGIN_PLUGIN_CFLAGS)
shinima_pidgin_plugin_la_LDFLAGS = \
	$(SHINIMA_PIDGIN_PLUGIN_LIBS) \
	-module -avoid-version -shared
