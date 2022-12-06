#pragma once
#include <jni.h>
#include <iostream>

namespace onionhook {
	class c_game_instance;
	class c_object_wrapper {
	public:
		c_object_wrapper(jobject object, JNIEnv* env, c_game_instance* game) {
			this->m_object = object;
			this->m_env = env;
			this->m_game = game;
		}

		jobject get_java_object();
		void free();

		// helpers
		jobject get_object_field(const std::string& name, const std::string& descriptor);
		jobject get_object_field(const jobject& object, const std::string& name, const std::string& descriptor);

		jfieldID get_field_id(const std::string& name, const std::string& descriptor);

		jmethodID get_method_id(const std::string& name, const std::string& descriptor);
		jmethodID get_method_id(const jobject& object, const std::string& name, const std::string& descriptor);

		void free(const jobject& object);
	protected:
		JNIEnv* m_env;
		c_game_instance* m_game;
		jobject m_object;
	};
}