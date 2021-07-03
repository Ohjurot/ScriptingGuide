#pragma once

#include <ConsoleGameLib/RandomWord.h>
#include <ConsoleGameLib/GameConsole.h>

#include <lua/lua.hpp>

// Java bindings
class LuaBind {
	public:
		static int Lua_RandomWord_getRandomWord(lua_State* ptrState);
		static int Lua_GameConsole_clearBuffer(lua_State* ptrState);
		static int Lua_GameConsole_present(lua_State* ptrState);
		static int Lua_GameConsole_putString(lua_State* ptrState);
};
