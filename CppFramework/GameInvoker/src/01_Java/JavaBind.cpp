#include "JavaBind.h"

jstring JavaBind::Java_RandomWord_getRandomWord(JNIEnv* env, jobject* sender) {
	return nullptr;
}

void JavaBind::Java_GameConsole_clearBuffer(JNIEnv* env, jobject* sender) {

}

void JavaBind::Java_GameConsole_present(JNIEnv* env, jobject* sender) {

}

void JavaBind::Java_GameConsole_putChar(JNIEnv* env, jobject* sender, jint x, jint y, jchar c) {

}

void JavaBind::Java_GameConsole_putString(JNIEnv* env, jobject* sender, jint x, jint y, jstring str, jboolean wrap) {

}
