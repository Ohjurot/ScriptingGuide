#pragma once

#include <WinInclude.h>
#include <IGame.h>

#include <lua/lua.hpp>

// A Lua game
class LuaGame : public IGame {
	public:
		// Constructor
		LuaGame();
		// Destructor
		~LuaGame();

		// Interface
		void keyEvent(char key) override;
		bool tick() override;

	private:
		// LUA VM
		lua_State* m_ptrLuaState = nullptr;
};
