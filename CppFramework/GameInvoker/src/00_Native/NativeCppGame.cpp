#include "NativeCppGame.h"


NativeCppGame::NativeCppGame() {
	// Get random word
	m_selectedWord = CGL::getRandomWord();
}

void NativeCppGame::keyEvent(char key) {
	// Get pointer to selcted char
	bool* selectPointer = &m_selectedChars[key - 'A'];
	
	// Check if currently not set
	if (!*selectPointer) {
		// Mark as selected
		*selectPointer = true;

		// Check if fail needs to be incremented
		const char* ptrChar = strchr(m_selectedWord, key);
		if (!ptrChar) {
			m_failes++;
		}

		// Redraw
		redraw();
	}
}

bool NativeCppGame::tick() {
	// Counting
	m_gameDuration++;

	// Check failes
	if (m_failes > 5) {
		CGL::Console::clearBuffer();
		CGL::Console::putString(30, 12, "You have LOST");

		std::stringstream ss;
		ss << "The word was: " << m_selectedWord;
		CGL::Console::putString(30, 13, ss.str().c_str());
		CGL::Console::present();

		Sleep(4000);

		return false;
	}

	// Check for win
	int matches = strlen(m_selectedWord);
	for (const char* ptrWord = m_selectedWord; *ptrWord; ptrWord++) {
		if (m_selectedChars[*ptrWord - 'A']) matches--;
	}

	if (matches == 0) {
		CGL::Console::clearBuffer();
		CGL::Console::putString(30, 12, "You have WON");

		std::stringstream ss;
		ss << "The word was: " << m_selectedWord;
		CGL::Console::putString(30, 13, ss.str().c_str());
		CGL::Console::present();

		Sleep(4000);

		return false;
	}

	// Redraw playfield
	if(m_gameDuration % 5 == 0) redraw();

	// Keep goint
	return true;
}

void NativeCppGame::redraw(){
	// Compute duration
	unsigned int mins = (m_gameDuration / 10) / 60;
	unsigned int secs = (m_gameDuration / 10) % 60;

	// Clear frame
	CGL::Console::clearBuffer();

	// Draw timer
	std::stringstream ss;
	ss << "Playtime: " << (mins < 10 ? "0" : "") << mins << ((m_gameDuration / 5) % 2 ? ":" : " ") << (secs < 10 ? "0" : "") << secs;
	CGL::Console::putString(0, 0, ss.str().c_str(), false);

	// Draw failures
	ss.str("");
	ss << "Failures: " << m_failes << " / 5";
	CGL::Console::putString(100, 0, ss.str().c_str(), false);

	// Draw keyset box
	CGL::Console::putString(40, 2, "*****************************");
	for (int i = 3; i < 8; i++) {
		CGL::Console::putChar(40, i, '*');
		CGL::Console::putChar(40+28, i, '*');
	}
	CGL::Console::putString(40, 8, "*****************************");
	
	// Draw keyset
	for (unsigned int key = 0; key < 26; key++) {
		int row = key / 13;
		int col = key % 13;

		CGL::Console::putChar(42 + 2 * col, 4 + row * 2, m_selectedChars[key] ? ' ' : m_charMap[key]);
	}

	// Draw info text
	CGL::Console::putString(37, 14, ">>> Try guessing the next char <<<");

	// Current guess
	ss.str("");
	ss << "Guessing the word: ";
	for (const char* wordPointer = m_selectedWord; *wordPointer; wordPointer++) {
		ss << (m_selectedChars[*wordPointer - 'A'] ? *wordPointer : '_') << " ";
	}
	CGL::Console::putString(0, 20, ss.str().c_str());

	// Render
	CGL::Console::present();
}
