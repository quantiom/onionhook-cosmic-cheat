#include "../../mappings.h"
#include "../header/c_class_handler.h"

namespace onionhook {
	void c_class_handler::setup_class_loader() {
		jclass thread_class = this->m_env->FindClass("java/lang/Thread");
		jmethodID get_thread_class_loader_method = this->m_env->GetMethodID(thread_class, "getContextClassLoader", "()Ljava/lang/ClassLoader;");

		jclass iterator_class = this->m_env->FindClass("java/util/Iterator");

		jmethodID get_thread_id_method = this->m_env->GetMethodID(thread_class, "getId", "()J");
		jmethodID get_threads_map_method = this->m_env->GetStaticMethodID(thread_class, "getAllStackTraces", "()Ljava/util/Map;");
		jmethodID get_threads_keyset_method = this->m_env->GetMethodID(this->m_env->FindClass("java/util/Map"), "keySet", "()Ljava/util/Set;");
		jmethodID get_set_iterator_method = this->m_env->GetMethodID(this->m_env->FindClass("java/util/Set"), "iterator", "()Ljava/util/Iterator;");
		jmethodID iterator_has_next_method = this->m_env->GetMethodID(iterator_class, "hasNext", "()Z");
		jmethodID iterator_next_method = this->m_env->GetMethodID(iterator_class, "next", "()Ljava/lang/Object;");

		jobject threads_map = this->m_env->CallStaticObjectMethod(thread_class, get_threads_map_method);
		jobject threads_keyset = this->m_env->CallObjectMethod(threads_map, get_threads_keyset_method);
		jobject threads_iterator = this->m_env->CallObjectMethod(threads_keyset, get_set_iterator_method);

		while (this->m_env->CallBooleanMethod(threads_iterator, iterator_has_next_method)) {
			jobject thread = this->m_env->CallObjectMethod(threads_iterator, iterator_next_method);
			long thread_id = this->m_env->CallLongMethod(thread, get_thread_id_method);

			if (thread_id == 1) {
				jobject main_thread_class_loader = this->m_env->CallObjectMethod(thread, get_thread_class_loader_method);
				m_main_thread_class_loader = this->m_env->NewGlobalRef(main_thread_class_loader);
				break;
			}
		}

		// Minecraft class
		jclass minecraft_class = get_class(mappings::get_class_name_mapping("Minecraft").m_name);
		const auto get_minecraft_mapping = mappings::get_method_mapping("Minecraft", "getMinecraft");

		jmethodID find_minecraft = this->m_env->GetStaticMethodID(minecraft_class, get_minecraft_mapping.m_name.c_str(), get_minecraft_mapping.m_signature.c_str());
		m_minecraft = this->m_env->NewGlobalRef(this->m_env->CallStaticObjectMethod(minecraft_class, find_minecraft));
	}

	jclass c_class_handler::get_class(std::string name) {
		if (cached_classes.contains(name)) {
			return static_cast<jclass>(cached_classes[name]);
		}

		return get_class_no_cache(name);
	}

	jclass c_class_handler::get_class_no_cache(std::string name) {
		jmethodID load_class_method = this->m_env->GetMethodID(this->m_env->FindClass("java/lang/ClassLoader"), "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");
		jclass clazz = static_cast<jclass>(this->m_env->CallObjectMethod(m_main_thread_class_loader, load_class_method, this->m_env->NewStringUTF(name.c_str())));

		if (clazz != nullptr) {
			cached_classes[name] = this->m_env->NewGlobalRef(clazz);
			return clazz;
		}

		return nullptr;
	}

	void c_class_handler::free_global_refs() {
		this->m_env->DeleteGlobalRef(m_minecraft);
		this->m_env->DeleteGlobalRef(m_main_thread_class_loader);

		for (const auto& [key, value] : cached_classes) {
			this->m_env->DeleteGlobalRef(value);
		}
	}
}