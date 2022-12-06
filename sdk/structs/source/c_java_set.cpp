#include "../header/c_java_set.h"

int c_java_set::size(jobject java_class) {
	jmethodID size = this->m_env->GetMethodID(this->m_env->GetObjectClass(java_class), "size", "()I");
	return this->m_env->CallIntMethod(java_class, size);
}

jobjectArray c_java_set::to_array(jobject java_class) {
	jmethodID to_array = this->m_env->GetMethodID(this->m_env->GetObjectClass(java_class), "toArray", "()[Ljava/lang/Object;");
	return (jobjectArray)this->m_env->CallObjectMethod(java_class, to_array);
}

jobject c_java_set::get(jobject java_class, int index) {
	jobjectArray java_class_array = to_array(java_class);
	if (!java_class_array) {
		return nullptr;
	}
	return this->m_env->GetObjectArrayElement(java_class_array, index);
}
