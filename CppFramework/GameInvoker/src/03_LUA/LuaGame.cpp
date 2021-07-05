#include "LuaGame.h"

LuaGame::LuaGame() {
    // Load LUA VM
    m_ptrLuaState = luaL_newstate();
    if (m_ptrLuaState) {
        // Load the lua std lib
        luaL_openlibs(m_ptrLuaState);

        // LUA Register functions
        lua_register(m_ptrLuaState, "getRandomWord", &LuaBind::Lua_RandomWord_getRandomWord);
        lua_register(m_ptrLuaState, "clearBuffer", &LuaBind::Lua_GameConsole_clearBuffer);
        lua_register(m_ptrLuaState, "present", &LuaBind::Lua_GameConsole_present);
        lua_register(m_ptrLuaState, "putString", &LuaBind::Lua_GameConsole_putString);

        // Load and parse HangmanScript.lua
        int resultL = luaL_loadfile(m_ptrLuaState, "./HangmanScript.lua");
        if (resultL == LUA_OK) {
            // Run plain script (run non in function code to init)
            resultL = lua_pcall(m_ptrLuaState, 0, LUA_MULTRET, 0);
            if (resultL == LUA_OK) {
                // Lua init was done properly
                m_luaOk = true;
            }
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
    // Only on valid lua
    if (m_luaOk) {
        // Call lua
        if (lua_getglobal(m_ptrLuaState, "keyEvent") == LUA_TFUNCTION) {
            // Push argument
            char charText[2] = { key, '\0' };
            lua_pushstring(m_ptrLuaState, charText);

            // Lua pcall
            lua_pcall(m_ptrLuaState, 1, 0, 0);
        }
    }
}

bool LuaGame::tick() {
    bool result = false;
    
    // Only on valid lua
    if (m_luaOk) {
        // Call lua
        if (lua_getglobal(m_ptrLuaState, "tick") == LUA_TFUNCTION) {
            if (lua_pcall(m_ptrLuaState, 0, 1, 0) == LUA_OK) {
                // Check and get result
                if (lua_isboolean(m_ptrLuaState, -1)) {
                    result = lua_toboolean(m_ptrLuaState, -1);
                }

                // Pop return value from stack
                lua_pop(m_ptrLuaState, 1);
            }
        }
    }

    // Return result
    return result;
}
