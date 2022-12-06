#pragma once
#include "c_object_wrapper.h"
#include "../../utils/vec.h"

namespace onionhook {
	class c_minecraft_vector : public c_object_wrapper {
	public:
		c_minecraft_vector(jobject object, JNIEnv* env, c_game_instance* game)
			: c_object_wrapper(object, env, game) {
		};

		// x, y, z
		vec3_t to_vec3() {
			auto clazz = this->m_env->GetObjectClass(this->m_object);

			const auto x_field_mapping = mappings::get_field_mapping("Vec3", "xCoord");
			const auto x_field = this->m_env->GetFieldID(clazz, x_field_mapping.m_name.c_str(), x_field_mapping.m_signature.c_str());

			const auto y_field_mapping = mappings::get_field_mapping("Vec3", "yCoord");
			const auto y_field = this->m_env->GetFieldID(clazz, y_field_mapping.m_name.c_str(), y_field_mapping.m_signature.c_str());

			const auto z_field_mapping = mappings::get_field_mapping("Vec3", "zCoord");
			const auto z_field = this->m_env->GetFieldID(clazz, z_field_mapping.m_name.c_str(), z_field_mapping.m_signature.c_str());

			float x = this->m_env->GetDoubleField(this->m_object, x_field);
			float y = this->m_env->GetDoubleField(this->m_object, y_field);
			float z = this->m_env->GetDoubleField(this->m_object, z_field);

			return { x, y, z };
		}

		static c_minecraft_vector from_vec3(vec3_t in, JNIEnv* env, c_game_instance* game);
	};
}