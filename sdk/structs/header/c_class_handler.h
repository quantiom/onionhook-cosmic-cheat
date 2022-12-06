#pragma once
#include <jni.h>
#include <unordered_map>

namespace onionhook {
	class c_class_handler {
	public:
		c_class_handler(JNIEnv* env) : m_env(env) {};

		void setup_class_loader();
		void free_global_refs();

		jclass get_class(std::string name);
		jclass get_class_no_cache(std::string name);

		inline jobject get_minecraft_ref() {
			return this->m_minecraft;
		}
	private:
		JNIEnv* m_env;

		// cached objects
		jobject m_main_thread_class_loader;
		jobject m_minecraft;

		std::unordered_map<std::string, jobject> cached_classes{};
	};
}