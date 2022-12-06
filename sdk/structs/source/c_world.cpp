#include "../header/c_world.h"
#include "../header/c_java_set.h"
#include "../header/c_game_instance.h"

#include "../../mappings.h"

#include <any>

namespace onionhook {
	// WorldClient#entityList.size()
	int c_world::get_num_entities() {
		const auto mapping = mappings::get_field_mapping("WorldClient", "entityList");

		c_java_set set = c_java_set(this->m_env);
		int size = set.size(this->m_env->GetObjectField(this->m_object, this->get_field_id(mapping.m_name, mapping.m_signature)));

		return size;
	}

	// World#playerEntities.size()
	int c_world::get_num_players() {
		const auto mapping = mappings::get_field_mapping("World", "playerEntities");

		c_java_set set = c_java_set(this->m_env);
		int size = set.size(this->m_env->GetObjectField(this->m_object, this->get_field_id(mapping.m_name, mapping.m_signature)));

		return size;
	}

	// World#playerEntities
	c_player c_world::get_player(int i) {
		const auto mapping = mappings::get_field_mapping("World", "playerEntities");

		c_java_set set = c_java_set(this->m_env);
		auto player = c_player(set.get(this->m_env->GetObjectField(this->m_object, this->get_field_id(mapping.m_name, mapping.m_signature)), i), this->m_env, this->m_game);

		return player;
	}

	// WorldClient#entityList
	c_entity c_world::get_entity(int i) {
		const auto mapping = mappings::get_field_mapping("WorldClient", "entityList");

		c_java_set set = c_java_set(this->m_env);
		auto entity = c_player(set.get(this->m_env->GetObjectField(this->m_object, this->get_field_id(mapping.m_name, mapping.m_signature)), i), this->m_env, this->m_game);

		return entity;
	}

	std::vector<c_entity> c_world::get_entities() {
		std::vector<c_entity> list{};

		for (int i = 0; i < this->get_num_entities(); i++) {
			list.push_back(this->get_entity(i));
		}

		return list;
	}

	std::vector<c_player> c_world::get_players() {
		std::vector<c_player> list{};

		for (int i = 0; i < this->get_num_players(); i++) {
			list.push_back(this->get_player(i));
		}

		return list;
	}

	std::vector<c_player> c_world::get_valid_players() {
		std::vector<c_player> list{};

		const auto local_player_id = this->m_game->get_player().get_id();

		for (int i = 0; i < this->get_num_players(); i++) {
			auto player = this->get_player(i);

			if (player.is_valid() && player.get_id() != local_player_id) list.push_back(player);
		}

		return list;
	}

	// World#rayTraceBlocks(Vec3 vec31, Vec3 vec32, boolean stopOnLiquid, boolean ignoreBlockWithoutBoundingBox, boolean returnLastUncollidableBlock)
	std::optional<c_moving_object_position> c_world::ray_trace(vec3_t _start, vec3_t _end) {
		/*auto start = c_minecraft_vector::from_vec3(_start, this->m_env, this->m_game);
		auto end = c_minecraft_vector::from_vec3(_end, this->m_env, this->m_game);

		const auto ray_trace_blocks_mapping = mappings::get_method_mapping("World", "rayTraceBlocks");
		const auto method_id = this->get_method_id(ray_trace_blocks_mapping.m_name, ray_trace_blocks_mapping.m_signature);

		std::deque<std::any> real_args = {start.get_java_object(), end.get_java_object(), JNI_FALSE, JNI_FALSE, JNI_TRUE};
		std::deque<std::any> final_args;

		for (int i = 0; i < ray_trace_blocks_mapping.total_args; i++) {
			if (ray_trace_blocks_mapping.encrypted_args.find(i) != ray_trace_blocks_mapping.encrypted_args.end()) {
				final_args.push_back(ray_trace_blocks_mapping.encrypted_args.at(i));
			} else {
				final_args.push_back(real_args.front());
				real_args.pop_front();
			}
		}

		const auto ray_hit = this->m_env->CallObjectMethod(this->m_object, method_id, 24360, (byte)1, start.get_java_object(), end.get_java_object(), JNI_FALSE, JNI_FALSE, 12999479, JNI_TRUE);

		start.free();
		end.free();

		if (ray_hit != nullptr) {
			return c_moving_object_position(ray_hit, this->m_env, this->m_game);
		}*/

		return {};
	}
}