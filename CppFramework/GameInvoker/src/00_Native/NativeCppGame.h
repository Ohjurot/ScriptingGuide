#pragma once

#include <string>
#include <sstream>

#include <WinInclude.h>
#include <IGame.h>
#include <ConsoleGameLib/GameConsole.h>
#include <ConsoleGameLib/RandomWord.h>

class NativeCppGame : public IGame {
	public:
		// Construct
		NativeCppGame();

		// Implement interface
		void keyEvent(char key) override;
		bool tick() override;

	private:
		// Redraw playfield
		void redraw();

	private:
		// Selected word
		const char* m_selectedWord = nullptr;
		// Failes
		unsigned int m_failes = 0;
		// Game duration
		unsigned int m_gameDuration = 0;
		// Charmap
		const char* m_charMap = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		// Currently selected chars
		bool m_selectedChars[26] = {};
};