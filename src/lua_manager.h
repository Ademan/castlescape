#pragma once

#ifndef LUA_MANAGER_H
#define LUA_MANAGER_H

extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}
void doLua();
typedef int (* PLUACALLBACK) (lua_State * L);
//FIXME: Not a very elegant wrapper for the LuaVM
class LuaManager
{
	lua_State* L;
public:
	LuaManager() 
	{ 
		L = luaL_newstate(); 
		luaL_openlibs(L);
	}
	~LuaManager() { lua_close(L); }
	lua_State* vm() { return L; }

	int load(const char * file)
	{
		return luaL_loadfile(L, file);
	}
	void reg_func(const char * name, PLUACALLBACK f)
	{
		lua_register(L, name, f);
	}
	const char* errors(const int state)
	{
		if (state != 0)
		{
			const char* temp = lua_tostring(L, -1);
			lua_pop(L, 1);
			return temp;
		}
		return NULL;
	}
	int exec(const int params, const int returns)
	{
		return lua_pcall(L, params, returns, 0);
	}
};

#endif
