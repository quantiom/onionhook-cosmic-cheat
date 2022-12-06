#pragma once
#include "c_minecraft_vector.h"

namespace onionhook {
	class c_moving_object_position : public c_object_wrapper {
	public:
		enum class hit_type {
			entity,
			block,
			miss
		};

		c_moving_object_position(jobject object, JNIEnv* env, c_game_instance* game)
			: c_object_wrapper(object, env, game) {
		};

		c_minecraft_vector get_hit_position() {
			const auto hit_position_mapping = mappings::get_field_mapping("MovingObjectPosition", "hitVec");
			return c_minecraft_vector(this->get_object_field(hit_position_mapping.m_name, hit_position_mapping.m_signature), this->m_env, this->m_game);
		}

		hit_type get_type_of_hit() {
			const auto type_of_hit_mapping = mappings::get_field_mapping("MovingObjectPosition", "typeOfHit");
			const auto enum_constant = this->get_object_field(type_of_hit_mapping.m_name, type_of_hit_mapping.m_signature);
			
			return (hit_type)this->m_env->CallIntMethod(enum_constant, this->get_method_id(enum_constant, "ordinal", "()I"));
		}

		std::optional<c_entity> get_entity_hit() {
			const auto entity_hit_mapping = mappings::get_field_mapping("MovingObjectPosition", "entityHit");
			const auto ent = this->get_object_field(entity_hit_mapping.m_name, entity_hit_mapping.m_signature);
		
			if (ent == NULL) return {};
			
			return c_entity(ent, this->m_env, this->m_game);
		}

		bool is_valid() {
			return this->m_object != nullptr;
		}
	};
}