#include "../header/c_object_wrapper.h"

namespace onionhook {
	jobject c_object_wrapper::get_java_object() {
		return this->m_object;
	}

	void c_object_wrapper::free() {
		this->m_env->DeleteLocalRef(this->m_object);
	}

	jobject c_object_wrapper::get_object_field(const std::string& name, const std::string& descriptor) {
		return this->get_object_field(this->m_object, name, descriptor);
	}

	jobject c_object_wrapper::get_object_field(const jobject& object, const std::string& name, const std::string& descriptor) {
		return this->m_env->GetObjectField(object, this->m_env->GetFieldID(this->m_env->GetObjectClass(object), name.c_str(), descriptor.c_str()));
	}

	jfieldID c_object_wrapper::get_field_id(const std::string& name, const std::string& descriptor) {
		return this->m_env->GetFieldID(this->m_env->GetObjectClass(this->m_object), name.c_str(), descriptor.c_str());
	}

	jmethodID c_object_wrapper::get_method_id(const jobject& object, const std::string& name, const std::string& descriptor) {
		return this->m_env->GetMethodID(this->m_env->GetObjectClass(object), name.c_str(), descriptor.c_str());
	}

	jmethodID c_object_wrapper::get_method_id(const std::string& name, const std::string& descriptor) {
		return this->m_env->GetMethodID(this->m_env->GetObjectClass(this->m_object), name.c_str(), descriptor.c_str());
	}

	void c_object_wrapper::free(const jobject& object) {
		this->m_env->DeleteLocalRef(object);
	}
}