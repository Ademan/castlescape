#include <iostream>
#include "lua_manager.h"

using std::cout;
using std::endl;

int my_function(lua_State * L)
{
	int argc = lua_gettop(L);
	cout << "Number of arguments: " << argc << endl;
	for (int i = 1; i <= argc; i++)
		cout << "Argument(" << i << "): " << lua_tostring(L, i) << endl;

	lua_pushnumber(L, 0xDEADBEEF);
	return 1;
}

void doLua()
{
	LuaManager L;
	int s;
	char* err;
	cout << "Starting lua!" << endl;
	L.reg_func("afunc", my_function);
	s = L.load("scripts/test2.lua");
	err = const_cast<char*>(L.errors(s));
	if (err)
		cout << err << endl;
	else
		s = L.exec(0, 0);
		err = const_cast<char*>(L.errors(s));
		if (err)
			cout << err << endl;
	cout << "Completed doing lua!" << endl;
}
