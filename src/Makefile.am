bin_PROGRAMS = lua-fastcgi

lua_fastcgi_SOURCES = lua-fastcgi.c lua-fastcgi.h \
	config.c config.h \
	lfuncs.c lfuncs.h \
	lf.c lf.h

lua_fastcgi_CFLAGS = $(LUA_CFLAGS) $(LFCGI_CFLAGS)
lua_fastcgi_LDADD = $(LUA_LIBS) -lfcgi -lpthread
