#include "JavaBind.h"

jstring JavaBind::Java_RandomWord_getRandomWord(JNIEnv* env, jobject* sender) {
	jstring outString = nullptr;
	
	// Geting and checking
	const char* randString = CGL::getRandomWord();
	if (randString) {
		outString = env->NewStringUTF(randString);
	}

	// Return strign
	return outString;
}

void JavaBind::Java_GameConsole_clearBuffer(JNIEnv* env, jobject* sender) {
	CGL::Console::clearBuffer();
}

void JavaBind::Java_GameConsole_present(JNIEnv* env, jobject* sender) {
	CGL::Console::present();
}

void JavaBind::Java_GameConsole_putChar(JNIEnv* env, jobject* sender, jint x, jint y, jchar c) {
	if (x >= 0 && y >= 0) {
		CGL::Console::putChar(x, y, c);
	}
}

void JavaBind::Java_GameConsole_putString(JNIEnv* env, jobject* sender, jint x, jint y, jstring str, jboolean wrap) {
	if (x >= 0 && y >= 0) {
		CGL::Console::putString(x, y, env->GetStringUTFChars(str, nullptr), wrap);
	}
}
