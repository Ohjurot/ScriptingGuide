#include <ConsoleGameLib/GameConsole.h>
#include <Implementation/GConsole.h>

void CGL::Console::clearBuffer() {
	// Get and check console pointer
	auto consolePointer = CGL_internal::GConsole::get();
	if (consolePointer) {
		// Redirect call
		consolePointer->clearBuffer();
	}
}

void CGL::Console::present() {
	// Get and check console pointer
	auto consolePointer = CGL_internal::GConsole::get();
	if (consolePointer) {
		// Redirect call
		consolePointer->present();
	}
}

void CGL::Console::putChar(unsigned int x, unsigned int y, char c) {
	// Get and check console pointer
	auto consolePointer = CGL_internal::GConsole::get();
	if (consolePointer) {
		// Redirect call
		consolePointer->putChar(x, y, c);
	}
}

void CGL::Console::putString(unsigned int x, unsigned int y, const char* string, bool wrap) {
	// Get and check console pointer
	auto consolePointer = CGL_internal::GConsole::get();
	if (consolePointer) {
		// Redirect call
		consolePointer->putString(x, y, string, wrap);
	}
}
