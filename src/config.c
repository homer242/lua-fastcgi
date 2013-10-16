#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "config.h"

// Create configuration with default settings
LF_config *LF_createconfig(void)
{
	LF_config *c = malloc(sizeof(LF_config));
	if(c == NULL){ return NULL; }

	// Default settings
	snprintf(c->listen, sizeof(c->listen), "127.0.0.1:9222");
	c->backlog = 100;
	c->threads = 1;
	c->sandbox = 1;
	c->mem_max = 65536;
	c->output_max = 65536;
	c->cpu_usec = 500000;
	c->cpu_sec  = 0;
	snprintf(c->content_type, sizeof(c->content_type),
		 "text/plain");

	return c;
}


// Load configuration
int LF_loadconfig(LF_config *cfg, const char *path)
{
	lua_Number lua_num;

	if(access(path, F_OK) != 0){ return 1; }

	lua_State *l = luaL_newstate();
	if(luaL_loadfile(l, path) || lua_pcall(l,0,1,0)){
		printf("%s\n", lua_tostring(l, -1));
		lua_close(l);
		return 1;
	}

	lua_settop(l, 1);

	if(lua_istable(l, 1)){
		lua_pushstring(l, "listen");
		lua_rawget(l, 1);
		if(lua_isstring(l, 2)){
			size_t len = 0;
			const char *str = lua_tolstring(l, 2, &len);

			if(len > 0){
				snprintf(cfg->listen, sizeof(cfg->listen),
					 "%s", str);
			}
		}

		lua_settop(l, 1);

		lua_pushstring(l, "backlog");
		lua_rawget(l, 1);
		if(lua_isnumber(l, 2)){
			lua_num = lua_tonumber(l, 2);
			if(lua_num < 0){
				fprintf(stderr, "Invalid backlog value: %d\n",
					(int)lua_num);
				return 1;
			}
			cfg->backlog = (unsigned int)lua_num;
		}

		lua_settop(l, 1);

		lua_pushstring(l, "threads");
		lua_rawget(l, 1);
		if(lua_isnumber(l, 2)){
			lua_num = lua_tonumber(l, 2);
			if(lua_num < 0){
				fprintf(stderr, "Invalid threads value: %d\n",
					(int)lua_num);
				return 1;
			}
			cfg->threads = (unsigned int)lua_num;
		}

		lua_settop(l, 1);

		lua_pushstring(l, "sandbox");
		lua_rawget(l, 1);
		if(lua_isboolean(l, 2)){ cfg->sandbox = lua_toboolean(l, 2); }

		lua_settop(l, 1);

		lua_pushstring(l, "mem_max");
		lua_rawget(l, 1);
		if(lua_isnumber(l, 2)){
			lua_num = lua_tonumber(l, 2);
			if(lua_num < 0){
				fprintf(stderr, "Invalid mem_max value: %d\n",
					(int)lua_num);
				return 1;
			}
			cfg->mem_max = (unsigned int)lua_num;
		}

		lua_settop(l, 1);

		lua_pushstring(l, "cpu_usec");
		lua_rawget(l, 1);
		if(lua_isnumber(l, 2)){
			lua_num = lua_tonumber(l, 2);
			if(lua_num < 0){
				fprintf(stderr, "Invalid cpu_usec value: %d\n",
					(int)lua_num);
				return 1;
			}
			cfg->cpu_usec = (long int)lua_num;
		}

		lua_settop(l, 1);

		lua_pushstring(l, "cpu_sec");
		lua_rawget(l, 1);
		if(lua_isnumber(l, 2)){
			lua_num = lua_tonumber(l, 2);
			if(lua_num < 0){
				fprintf(stderr, "Invalid cpu_usec value: %d\n",
					(int)lua_num);
				return 1;
			}
			cfg->cpu_sec = (long int)lua_num;
		}

		lua_settop(l, 1);

		lua_pushstring(l, "output_max");
		lua_rawget(l, 1);
		if(lua_isnumber(l, 2)){
			lua_num = lua_tonumber(l, 2);
			if(lua_num < 0){
				fprintf(stderr, "Invalid mem_max value: %d\n",
					(int)lua_num);
				return 1;
			}
			cfg->output_max = (size_t)lua_num;
		}

		lua_settop(l, 1);

		lua_pushstring(l, "content_type");
		lua_rawget(l, 1);
		if(lua_isstring(l, 2)){
			size_t len = 0;
			const char *str = lua_tolstring(l, 2, &len);

			if(len > 0){
				snprintf(cfg->content_type, sizeof(cfg->content_type),
					 "%s", str);
			}
		}
	}

	lua_close(l);
	return 0;
}
