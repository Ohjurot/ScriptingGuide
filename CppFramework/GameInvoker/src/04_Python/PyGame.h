#pragma once

#include <WinInclude.h>
#include <IGame.h>

#include <Python.h>

// A Lua game
class PyGame : public IGame {
	public:
		// Constructor
		PyGame();
		// Destructor
		~PyGame();

		// Interface
		void keyEvent(char key) override;
		bool tick() override;

	private:
		// 
};
