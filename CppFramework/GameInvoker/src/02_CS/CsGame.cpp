#include "CsGame.h"

CsGame::CsGame() {
	// Current directory as mono dir
	mono_set_dirs(".", ".");
	
	// Create mono domain
	m_ptrMonoDomain = mono_jit_init("CsGame");
	if (m_ptrMonoDomain) {
		// Load a mono assembly HangmanScript.dll
		m_ptrGameAssembly = mono_domain_assembly_open(m_ptrMonoDomain, "HangmanScript.dll");
		if (m_ptrGameAssembly) {
			// Loading mono image
			m_ptrGameAssemblyImage = mono_assembly_get_image(m_ptrGameAssembly);
			if (m_ptrGameAssemblyImage) {
				// Add internal calls
				mono_add_internal_call("CGL.RandomWord::getRandomWord()", &CsBind::CS_RandomWord_getRandomWord);
				mono_add_internal_call("CGL.GameConsole::clearBuffer()", &CGL::Console::clearBuffer);
				mono_add_internal_call("CGL.GameConsole::present()", &CGL::Console::present);
				mono_add_internal_call("CGL.GameConsole::putChar(uint,uint,char)", &CGL::Console::putChar);
				mono_add_internal_call("CGL.GameConsole::putString(uint,uint,string,bool)", &CsBind::CS_GameConsole_putString);

				// Find IGame
				MonoClass* ptrIGameClass = mono_class_from_name(m_ptrGameAssemblyImage, "HangmanScript", "IGame");
				MonoClass* ptrMainClass = mono_class_from_name(m_ptrGameAssemblyImage, "HangmanScript", "HangMain");
				if (ptrIGameClass && ptrMainClass) {
					// Describe method
					MonoMethodDesc* ptrMainMethodDesc = mono_method_desc_new(".HangMain:main()", false);
					if (ptrMainMethodDesc) {
						// Find main in mainclass
						MonoMethod* ptrMainMethod = mono_method_desc_search_in_class(ptrMainMethodDesc, ptrMainClass);
						if (ptrMainMethod) {
							// Call main method
							MonoObject* ptrExObject = nullptr;
							m_ptrGameObject = mono_runtime_invoke(ptrMainMethod, nullptr, nullptr, &ptrExObject);
							if (m_ptrGameObject) {
								// Ref count object on c++ side
								m_gameObjectGCHandle = mono_gchandle_new(m_ptrGameObject, false);

								// Get tick function
								MonoMethodDesc* ptrTickMethodDesc = mono_method_desc_new(".IGame:tick()", false);
								if (ptrTickMethodDesc) {
									// Get real function
									MonoMethod* virtualMethod = mono_method_desc_search_in_class(ptrTickMethodDesc, ptrIGameClass);
									if (virtualMethod) {
										m_ptrTickMethod = mono_object_get_virtual_method(m_ptrGameObject, virtualMethod);
									}

									// Free
									mono_method_desc_free(ptrTickMethodDesc);
								}

								// Get key event function
								MonoMethodDesc* ptrKeyMethodDesc = mono_method_desc_new(".IGame:keyEvent(char)", false);
								if (ptrKeyMethodDesc) {
									// Get real function
									MonoMethod* virtualMethod = mono_method_desc_search_in_class(ptrKeyMethodDesc, ptrIGameClass);
									if (virtualMethod) {
										m_ptrKeyEventMethod = mono_object_get_virtual_method(m_ptrGameObject, virtualMethod);
									}

									// Free
									mono_method_desc_free(ptrKeyMethodDesc);
								}
							}

							// Report exception
							if (ptrExObject) {
								MonoString* exString = mono_object_to_string(ptrExObject, nullptr);
								const char* exCString = mono_string_to_utf8(exString);
								MessageBoxA(NULL, exCString, "Mono Invoke issue", MB_OK | MB_ICONERROR);
							}
						}

						// Free desc
						mono_method_desc_free(ptrMainMethodDesc);
					}
				}
			}
		}
	}
}

CsGame::~CsGame() {
	// Release mono handles
	if (m_gameObjectGCHandle) {
		mono_gchandle_free(m_gameObjectGCHandle);
	}

	// Release the domain
	if (m_ptrMonoDomain) {
		mono_jit_cleanup(m_ptrMonoDomain);
	}
}

void CsGame::keyEvent(char key) {
	// Only if populated
	if (m_ptrKeyEventMethod) {
		// Invoke with exeetion
		MonoObject* ptrExObject = nullptr;
		void* args[] = {
			&key
		};
		mono_runtime_invoke(m_ptrKeyEventMethod, m_ptrGameObject, args, &ptrExObject);

		// Report exception
		if (ptrExObject) {
			MonoString* exString = mono_object_to_string(ptrExObject, nullptr);
			const char* exCString = mono_string_to_utf8(exString);
			MessageBoxA(NULL, exCString, "Mono Invoke issue", MB_OK | MB_ICONERROR);
		}
	}
}

bool CsGame::tick() {
	bool result = false;

	// Only if populated
	if (m_ptrTickMethod) {
		// Invoke with exeetion
		MonoObject* ptrExObject = nullptr;
		MonoObject* ptrReturnObject = mono_runtime_invoke(m_ptrTickMethod, m_ptrGameObject, nullptr, &ptrExObject);

		// Exetract bool if result was ok
		if (ptrReturnObject) {
			result = *(bool*)mono_object_unbox(ptrReturnObject);
		}

		// Report exception
		if (ptrExObject) {
			MonoString* exString = mono_object_to_string(ptrExObject, nullptr);
			const char* exCString = mono_string_to_utf8(exString);
			MessageBoxA(NULL, exCString, "Mono Invoke issue", MB_OK | MB_ICONERROR);
		}
	}

	// Return result
	return result;
}
