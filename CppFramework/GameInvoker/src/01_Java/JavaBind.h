#pragma once

#include <jni.h>

#include <ConsoleGameLib/RandomWord.h>
#include <ConsoleGameLib/GameConsole.h>

// Java bindings
class JavaBind {
	public:
		static jstring Java_RandomWord_getRandomWord(JNIEnv* env, jobject* sender);
		static void Java_GameConsole_clearBuffer(JNIEnv* env, jobject* sender);
		static void Java_GameConsole_present(JNIEnv* env, jobject* sender);
		static void Java_GameConsole_putChar(JNIEnv* env, jobject* sender, jint x, jint y, jchar c);
		static void Java_GameConsole_putString(JNIEnv* env, jobject* sender, jint x, jint y, jstring str, jboolean wrap);
};