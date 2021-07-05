#pragma once

#include <ConsoleGameLib/RandomWord.h>
#include <ConsoleGameLib/GameConsole.h>

#include <Python.h>

// Python bindings
class PyBind {
	public:
		static PyObject* Py_import();

		// Function modules
		static PyObject* Py_RandomWord_getRandomWord(PyObject* object, PyObject* args);
		static PyObject* Py_GameConsole_clearBuffer(PyObject* object, PyObject* args);
		static PyObject* Py_GameConsole_present(PyObject* object, PyObject* args);
		static PyObject* Py_GameConsole_putString(PyObject* object, PyObject* args);
};
