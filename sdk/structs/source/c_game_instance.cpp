#include "../header/c_game_instance.h"
#include "../../mappings.h"

namespace onionhook {
	jobject c_game_instance::get_minecraft() {
		return this->m_class_handler->get_minecraft_ref();
	}

	c_entity c_game_instance::get_player() {
		const auto the_player_mapping = mappings::get_field_mapping("Minecraft", "thePlayer");
		const auto the_player_field_id = this->m_env->GetFieldID(this->m_env->GetObjectClass(get_minecraft()), the_player_mapping.m_name.c_str(), the_player_mapping.m_signature.c_str());

		return c_entity(this->m_env->GetObjectField(get_minecraft(), the_player_field_id), this->m_env, this);
	}

	c_world c_game_instance::get_world() {
		const auto the_world_mapping = mappings::get_field_mapping("Minecraft", "theWorld");
		const auto the_world_field_id = this->m_env->GetFieldID(this->m_env->GetObjectClass(get_minecraft()), the_world_mapping.m_name.c_str(), the_world_mapping.m_signature.c_str());

		return c_world(this->m_env->GetObjectField(get_minecraft(), the_world_field_id), this->m_env, this);
	}

	bool c_game_instance::has_focus() {
		const auto has_focus_mapping = mappings::get_field_mapping("Minecraft", "inGameHasFocus");
		const auto has_focus_field_id = this->m_env->GetFieldID(this->m_env->GetObjectClass(get_minecraft()), has_focus_mapping.m_name.c_str(), has_focus_mapping.m_signature.c_str());

		return this->m_env->GetBooleanField(this->get_minecraft(), has_focus_field_id) == JNI_TRUE ? true : false; 
	}
}