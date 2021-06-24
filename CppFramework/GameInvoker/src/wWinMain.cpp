#include <WinInclude.h>
#include <ConsoleGameLib/GameConsole.h>
#include <ConsoleGameLib/RandomWord.h>

#include <Common/Input.h>
#include <IGame.h>

// Impls
#include <00_Native/NativeCppGame.h>
#include <01_Java/JavaGame.h>

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

INT WINAPI wWinMain(HINSTANCE _In_ hInstance, HINSTANCE _In_opt_ hPrevInstance, PWSTR _In_ cmdLine, INT _In_ cmdShow) {
	// Load console lib
	if (!LoadLibrary(L"ConsoleGameLib.dll")) {
		return -1;
	}
	
	// Show select aproach
	CGL::Console::clearBuffer();
	CGL::Console::putString(5, 2, "=== Select runtime aproach ===", false);
	CGL::Console::putString(5, 4, "A - Native C++ Implementation", false);
	CGL::Console::putString(5, 5, "B - Jave JRE Implementation", false);
	CGL::Console::putString(5, 6, "C - C# mono Implementation", false);
	CGL::Console::putString(5, 7, "D - Lua Implementation", false);
	CGL::Console::putString(5, 8, "E - Python Implementation", false);
	CGL::Console::putString(5, 9, "F - Angelscript Implementation", false);
	CGL::Console::present();

	// Do select prompt
	IGame* ptrGame = nullptr;
	while (true) {
		// Call to implemntation
		char selection = CommonInput::getInput();
		if (selection != ' ') {
			// Switch on selection
			switch (selection) {
				// Native C++
				case 'A':
					// Init native
					ptrGame = new NativeCppGame();
					break;

				// Java
				case 'B':
					ptrGame = new JavaGame();
					break;
				
				// Fallback
				default:
					CGL::Console::clearBuffer();
					CGL::Console::putString(0, 0, "Input not reconized! Application terminating...");
					CGL::Console::present();
					Sleep(2000);
			}
			break;
		}

		// Free this core
		SwitchToThread();
	}

	Sleep(500);

	// Execute game
	if (ptrGame) {
		// Timing integers
		LARGE_INTEGER timeFreqency, lastFrameTime, currentFrameTime;
		float deltaTimeMs = 0;

		// Query timer
		QueryPerformanceFrequency(&timeFreqency);
		QueryPerformanceCounter(&lastFrameTime);

		// Game loop
		bool keepRunning = true;
		while (keepRunning) {
			// Get time
			QueryPerformanceCounter(&currentFrameTime);

			// Compute delta in ms
			LARGE_INTEGER delta;
			delta.QuadPart = currentFrameTime.QuadPart - lastFrameTime.QuadPart;
			delta.QuadPart *= 1000000;
			delta.QuadPart /= timeFreqency.QuadPart;
			deltaTimeMs += delta.QuadPart / 1000.f;

			// Refresh last time
			lastFrameTime.QuadPart = currentFrameTime.QuadPart;
			if (deltaTimeMs >= 1000.0f) {
				deltaTimeMs = 0.0f;
				keepRunning = ptrGame->tick();
			}

			// Check key events
			char keyCode = CommonInput::getInput();
			if (keyCode != ' ') 
				ptrGame->keyEvent(keyCode);

			// Make space for windows
			SwitchToThread();
		}

		// Delete game
		delete ptrGame;
	}

	// Return OK
	return 0;
}