#include "LuaBind.h"

int LuaBind::Lua_RandomWord_getRandomWord(lua_State* ptrState) {
    int result = 0;

    // Get random word
    const char* rdWord = CGL::getRandomWord();
    if (rdWord) {
        lua_pushstring(ptrState, rdWord);
        result = 1;
    }

    // Return result
    return result;
}

int LuaBind::Lua_GameConsole_clearBuffer(lua_State* ptrState) {
    CGL::Console::clearBuffer();
    return 0;
}

int LuaBind::Lua_GameConsole_present(lua_State* ptrState) {
    CGL::Console::present();
    return 0;
}

int LuaBind::Lua_GameConsole_putString(lua_State* ptrState) {
    // 1: X
    // 2: Y
    // 3: String
    // (4: bool wrap)

    // Check 1-3
    if (lua_isinteger(ptrState, 1) && lua_isinteger(ptrState, 2) && lua_isstring(ptrState, 3)) {
        // Exetract
        auto x = lua_tointeger(ptrState, 1);
        auto y = lua_tointeger(ptrState, 2);
        const char* str = lua_tostring(ptrState, 3);

        // Check bound
        if (x >= 0 && y >= 0) {
            // Boolean 
            bool wrap = true;
            if (lua_isboolean(ptrState, 4)) {
                wrap = lua_toboolean(ptrState, 4);
            }

            // Redirect
            CGL::Console::putString(x, y, str, wrap);
        }
    }
    
    // void
    return 0;
}
