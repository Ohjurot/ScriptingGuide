#include "PyGame.h"

PyGame::PyGame() {
    // Set programm name
    Py_SetProgramName(L"PyGame");

    // Init py
    Py_Initialize();
    if (Py_IsInitialized()) {
       
    }
}

PyGame::~PyGame() {

    // Uninit
    Py_Finalize();
}

void PyGame::keyEvent(char key) {

}

bool PyGame::tick() {
    return false;
}
