#include "PyBind.h"

PyObject* PyBind::Py_import() {
    // Describe methods to bind
    static PyMethodDef bindMethods[] = {
        {"getRandomWord",   &PyBind::Py_RandomWord_getRandomWord,   METH_NOARGS,     "Retrive a random word"                 },
        {"clearBuffer",     &PyBind::Py_GameConsole_clearBuffer,    METH_NOARGS,     "Clear the console buffer"              },
        {"present",         &PyBind::Py_GameConsole_present,        METH_NOARGS,     "Present the console buffer"            },
        {"putString",       &PyBind::Py_GameConsole_putString,      METH_VARARGS,    "Put a string on the console buffer"    },
        {nullptr,           nullptr,                                0,               nullptr                                 },
    };

    // Describe module
    static PyModuleDef CGLModuleDef = {
        PyModuleDef_HEAD_INIT,
        "CGL", "Console Game Lib",
        -1, &bindMethods[0],
        nullptr, nullptr, nullptr, nullptr
    };
    
    return PyModule_Create(&CGLModuleDef);
}

PyObject* PyBind::Py_RandomWord_getRandomWord(PyObject* object, PyObject* args) {
    PyObject* rndPyStr = Py_None;
    
    // Get string
    const char* rndWord = CGL::getRandomWord();
    if (rndWord) {
        rndPyStr = PyUnicode_FromString(rndWord);
    }

    // Return string
    return rndPyStr;
}

PyObject* PyBind::Py_GameConsole_clearBuffer(PyObject* object, PyObject* args) {
    CGL::Console::clearBuffer();
    return Py_None;
}

PyObject* PyBind::Py_GameConsole_present(PyObject* object, PyObject* args) {
    CGL::Console::present();
    return Py_None;
}

PyObject* PyBind::Py_GameConsole_putString(PyObject* object, PyObject* args) {
    // ...
    if (!args)
        return Py_None;
    
    // Only if size if 3 or 4
    auto argsSize = PyTuple_Size(args);
    if (argsSize == 3 || argsSize == 4) {
        // Get base args
        PyObject* arg0 = PyTuple_GetItem(args, 0);
        PyObject* arg1 = PyTuple_GetItem(args, 1);
        PyObject* arg2 = PyTuple_GetItem(args, 2);

        // Check types
        if (arg0 && arg1 && arg2 && PyLong_Check(arg0) && PyLong_Check(arg1) && PyUnicode_Check(arg2)) {
            // Extract
            long x = PyLong_AsLong(arg0);
            long y = PyLong_AsLong(arg1);
            const char* str = PyUnicode_AsUTF8(arg2);

            // Check
            if (x >= 0 && y >= 0) {
                // Check warap
                bool wrap = false;
                if (argsSize == 4) {
                    PyObject* arg3 = PyTuple_GetItem(args, 3);
                    if (arg3 && PyBool_Check(arg3)) {
                        // Get
                        wrap = PyObject_IsTrue(arg3);
                    }
                }

                // Call
                CGL::Console::putString(x, y, str, wrap);
            }
        }
    }

    return Py_None;
}
