#include <WinInclude.h>
#include <cstdlib>
#include <ctime>

#include <Implementation/GConsole.h>
#include <Implementation/RWord.h>

// Dll entry point
BOOL WINAPI DllMain(HINSTANCE _In_ hInstance, DWORD _In_ callReason, LPVOID _In_opt_ reserved) {
	// Switch on call reson
	switch (callReason) {
		// Load DLL
		case DLL_PROCESS_ATTACH: {
			BOOL loadResult = FALSE;
			
			// Random seed
			srand(time(NULL));

			// Load 
			if (CGL_internal::GConsole::init() && CGL_internal::RWord::init(".\\words.txt")) {
				// Load ok
				loadResult = TRUE;
			}

			// Return result
			return loadResult;
		}

		// Unload DLL
		case DLL_PROCESS_DETACH: {
			// Unload
			CGL_internal::GConsole::destroy();
			CGL_internal::RWord::destroy();

			// Falltrought
		}

		// Default succeed
		default: {
			return TRUE;
		}
	}
}