#pragma once

#include <WinInclude.h>
#include <IGame.h>

#include <Python.h>

#include <04_Python/PyBind.h>

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
		// Python object
		PyObject* m_ptrPyModule = nullptr;
		PyObject* m_ptrTickFunction = nullptr;
		PyObject* m_ptrKeyEventFunction = nullptr;
};
