#pragma once

#include <WinInclude.h>
#include <ConsoleGameLib/ConsoleGameLib.h>
#include <cstdlib>

#define CGL_internal_CONSOLE_WIDTH 119
#define CGL_internal_CONSOLE_HEIGHT 29

namespace CGL_internal {
	// GConsole
	class GConsole {
		// Class Interface
		public:
			// Destruct
			~GConsole();

			// Implement "interface"
			void clearBuffer();
			void present();
			void putChar(unsigned int x, unsigned int y, char c);
			void putString(unsigned int x, unsigned int y, const char* string, bool wrap);

		private:
			// Console handle
			HANDLE m_hConsole = INVALID_HANDLE_VALUE;

			// Console buffer array
			char m_consoleBuffer[(CGL_internal_CONSOLE_WIDTH + 1) * CGL_internal_CONSOLE_HEIGHT + 1] = {};

		// Singelton
		public:
			// Init and destroy
			static bool init();
			static void destroy();

			// Get singelton
			static GConsole* get();

		private:
			// Private constructor
			GConsole();

			// Static instance pointer
			static GConsole* s_ptrInstance;
	};
}