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
			// Find required classes
			jclass nativeWordClass = m_ptrJavaEnv->FindClass("console/game/lib/RandomWord");
			jclass nativeConsoleClass = m_ptrJavaEnv->FindClass("console/game/lib/GameConsole");
			jclass hangClass = m_ptrJavaEnv->FindClass("game/java/hangman/HangMain");
			if (nativeWordClass && nativeConsoleClass && hangClass) {
				// Register natives for Random word
				JNINativeMethod nmWord[1];
				nmWord[0].name = (char*)"getRandomWord";
				nmWord[0].signature = (char*)"()Ljava/lang/String;";
				nmWord[0].fnPtr = &JavaBind::Java_RandomWord_getRandomWord;
				jint res1 = m_ptrJavaEnv->RegisterNatives(nativeWordClass, nmWord, 1);

				// Register natives for Console
				JNINativeMethod nmConsole[4];
				nmConsole[0].name = (char*)"clearBuffer";
				nmConsole[0].signature = (char*)"()V";
				nmConsole[0].fnPtr = &JavaBind::Java_GameConsole_clearBuffer;
				nmConsole[1].name = (char*)"present";
				nmConsole[1].signature = (char*)"()V";
				nmConsole[1].fnPtr = &JavaBind::Java_GameConsole_present;
				nmConsole[2].name = (char*)"putChar";
				nmConsole[2].signature = (char*)"(IIC)V";
				nmConsole[2].fnPtr = &JavaBind::Java_GameConsole_putChar;
				nmConsole[3].name = (char*)"putString";
				nmConsole[3].signature = (char*)"(IILjava/lang/String;Z)V";
				nmConsole[3].fnPtr = &JavaBind::Java_GameConsole_putString;
				jint res2 = m_ptrJavaEnv->RegisterNatives(nativeConsoleClass, nmConsole, 4);

				// Check function registerings
				if (res1 == JNI_OK && res2 == JNI_OK) {
					// Find the interface class
					m_iGameInterface = m_ptrJavaEnv->FindClass("game/java/IGame");
					if (m_iGameInterface) {
						// Find the static function
						jmethodID mainFunctionID = m_ptrJavaEnv->GetStaticMethodID(hangClass, "main", "()Lgame/java/IGame;");
						if (mainFunctionID) {
							// Call the static function
							m_gameObject = m_ptrJavaEnv->CallStaticObjectMethod(hangClass, mainFunctionID);
							if (m_gameObject && m_ptrJavaEnv->IsInstanceOf(m_gameObject, m_iGameInterface)) {
								// Get tick and event function
								m_mID_keyEvent = m_ptrJavaEnv->GetMethodID(m_iGameInterface, "keyEvent", "(C)V");
								m_mID_tick = m_ptrJavaEnv->GetMethodID(m_iGameInterface, "tick", "()Z");
							}
						}
					}
				}
			}

			// Prevent memory leak
			if (nativeWordClass) m_ptrJavaEnv->DeleteLocalRef(nativeWordClass);
			if (nativeConsoleClass) m_ptrJavaEnv->DeleteLocalRef(nativeConsoleClass);
			if (hangClass) m_ptrJavaEnv->DeleteLocalRef(hangClass);

			// Report execption
			m_ptrJavaEnv->ExceptionDescribe();
		}
	}
}

JavaGame::~JavaGame() {
	// Releasing object refs
	if (m_gameObject) m_ptrJavaEnv->DeleteLocalRef(m_gameObject);
	if (m_iGameInterface) m_ptrJavaEnv->DeleteLocalRef(m_iGameInterface);
	
	// Release Java VM
	if (m_ptrJavaVM) {
		// Destroy VM
		m_ptrJavaVM->DestroyJavaVM();
	}
}

void JavaGame::keyEvent(char key) {
	// Call if valid
	if (m_mID_keyEvent) {
		m_ptrJavaEnv->CallVoidMethod(m_gameObject, m_mID_keyEvent, key);
	}
}

bool JavaGame::tick() {
	return m_mID_tick ? m_ptrJavaEnv->CallBooleanMethod(m_gameObject, m_mID_tick) : false;
}
