#include "PyGame.h"

PyGame::PyGame() {
    // Set programm name
    Py_SetProgramName(L"PyGame");

    // Include modules
    PyImport_AppendInittab("CGL", &PyBind::Py_import);

    // Init py
    Py_Initialize();
    if (Py_IsInitialized()) {
        // Python bytecode
        PyObject* ptrByteCode = nullptr;
        
        // Load python file
        HANDLE hPythonSource = CreateFileW(
            L".\\HangmanScript.py", 
            GENERIC_READ, FILE_SHARE_READ, 
            NULL, 
            OPEN_EXISTING, 
            FILE_ATTRIBUTE_NORMAL, NULL
        );
        if (hPythonSource != INVALID_HANDLE_VALUE) {
            // Get file size
            DWORD fileSize = GetFileSize(hPythonSource, NULL);
            char* fileBuffer = (char*)malloc(fileSize + 1);
            if (fileBuffer) {
                // Read File
                if (ReadFile(hPythonSource, fileBuffer, fileSize, NULL, NULL)) {
                    // Null terminator
                    fileBuffer[fileSize] = '\0';

                    // Compile python code
                    ptrByteCode = Py_CompileString(fileBuffer, "HangmanScript.py", Py_file_input);
                }

                // Free memory if valid
                free(fileBuffer);
            }

            // Close file
            CloseHandle(hPythonSource);
        }
        
        // Load Module
        if (ptrByteCode) {
            m_ptrPyModule = PyImport_ExecCodeModule("HangmanScript", ptrByteCode);

            // Get functions
            if (m_ptrPyModule) {
                // Get functions
                m_ptrTickFunction = PyObject_GetAttrString(m_ptrPyModule, "tick");
                m_ptrKeyEventFunction = PyObject_GetAttrString(m_ptrPyModule, "keyEvent");
            }

            // Free bytecode
            Py_DECREF(ptrByteCode);
        }
    }
}

PyGame::~PyGame() {
    // Decrefs
    if (m_ptrKeyEventFunction) Py_DECREF(m_ptrKeyEventFunction);
    if (m_ptrTickFunction) Py_DECREF(m_ptrTickFunction);
    if (m_ptrPyModule) Py_DECREF(m_ptrPyModule);

    // Uninit
    Py_Finalize();
}

void PyGame::keyEvent(char key) {
    // Only if function is availble
    if (m_ptrKeyEventFunction) {
        // Pack arguemnts
        PyObject* ptrArgs = PyTuple_Pack(1, _PyUnicode_FromASCII(&key, 1));
        if (ptrArgs) {
            // Call
            PyObject* ptrResult = PyObject_CallObject(m_ptrKeyEventFunction, ptrArgs);
            if (ptrResult) {
                Py_DECREF(ptrResult);
            }

            // Decref
            Py_DECREF(ptrArgs);
        }
    }
}

bool PyGame::tick() {
    bool result = false;

    // Only if function is avilble
    if (m_ptrTickFunction) {
        // Call python
        PyObject* ptrResult = PyObject_CallObject(m_ptrTickFunction, nullptr);
        if (ptrResult) {
            if (PyBool_Check(ptrResult)) {
                result = PyObject_IsTrue(ptrResult);
            }

            // Decref
            Py_DECREF(ptrResult);
        }
    }

    // Return final result
    return result;
}
