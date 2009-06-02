#pragma once

#ifndef LUA_MANAGER_H
#define LUA_MANAGER_H

extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

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
};

#endif
