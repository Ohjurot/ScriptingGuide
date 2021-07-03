#include "LuaGame.h"

LuaGame::LuaGame() {
    // Load LUA VM
    m_ptrLuaState = luaL_newstate();
    if (m_ptrLuaState) {
        // Load the lua std lib
        luaL_openlibs(m_ptrLuaState);

        // LUA Register functions

        // Load and parse HangmanScript.lua
        int result = luaL_loadfile(m_ptrLuaState, "./HangmanScript.lua");
        if (result == 0) {
            int i = 0;
        }
    }
}

LuaGame::~LuaGame() {
    // Destroy LUA VM
    if (m_ptrLuaState) {
        lua_close(m_ptrLuaState);
    }
}

void LuaGame::keyEvent(char key) {

}

bool LuaGame::tick() {
    return false;
}
