#include "JavaGame.h"

JavaGame::JavaGame() {
	if (LoadLibrary(L"./jre/bin/server/jvm.dll")) {
		// Get application dir
		char appDir[2048];
		GetModuleFileNameA(GetModuleHandle(NULL), appDir, 2048);
		char* lastSlash = strrchr(appDir, '\\');
		lastSlash[1] = '\0';
		
		// Build java jar location
		std::stringstream ss;
		ss << "-Djava.class.path=" << appDir << "HangmanScript.jar";
		std::string option1String = ss.str();

		// Jave option
		JavaVMOption javaOptions[1] = {};
		javaOptions[0].optionString = &option1String[0];
		javaOptions[0].extraInfo = nullptr;

		// Java arguments
		JavaVMInitArgs javaArgs;
		javaArgs.ignoreUnrecognized = false;
		javaArgs.version = JNI_VERSION_1_8;
		javaArgs.nOptions = __crt_countof(javaOptions);
		javaArgs.options = javaOptions;
		
		// Init java vm
		if (JNI_CreateJavaVM(&m_ptrJavaVM, (void**)&m_ptrJavaEnv, &javaArgs) == JNI_OK) {

			// Check if jar was load ok
			jclass hangclass = m_ptrJavaEnv->FindClass("game/java/hangman/HangMain");

			// ...
			return;
		}
	}
}

JavaGame::~JavaGame() {
	// Release Java VM
	if (m_ptrJavaVM) {
		// Destroy VM
		m_ptrJavaVM->DestroyJavaVM();
	}
}

void JavaGame::keyEvent(char key) {

}

bool JavaGame::tick() {
	return false;
}
