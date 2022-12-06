#pragma once
#include <jni.h>

// disclaimer from quantiom
// i did not make this dogshit wrapper and i will not improve it either so sorry if you are reading this

class c_java_set {
public:
	c_java_set() {}
	c_java_set(JNIEnv* env) {
		m_env = env;
	}

	int size(jobject java_class);
	jobjectArray to_array(jobject java_class);
	jobject get(jobject java_class, int index);

private:
	JNIEnv* m_env;
};