#pragma once

#include <WinInclude.h>

#define EVAL_KEY(key, varname) if (GetAsyncKeyState(key)) varname = key

// Input class
class CommonInput {
	public:
		// Retrive pressed char
		static char getInput();

};