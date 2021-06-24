#pragma once

#include <WinInclude.h>
#include <IGame.h>
#include <01_Java/JavaBind.h>

#include <jni.h>

#include <string>
#include <sstream>
#include <cstring>

// A Java game
class JavaGame : public IGame {
	public:
		// Constructor
		JavaGame();
		// Destructor
		~JavaGame();

		// Interface
		void keyEvent(char key) override;
		bool tick() override;

	private:
		// Java VM Contianer
		JavaVM* m_ptrJavaVM = nullptr;

		// Java enviroment
		JNIEnv* m_ptrJavaEnv = nullptr;

		// Members
		jclass m_iGameInterface = nullptr;
		jobject m_gameObject = nullptr;
		jmethodID m_mID_keyEvent = nullptr;
		jmethodID m_mID_tick = nullptr;
};
