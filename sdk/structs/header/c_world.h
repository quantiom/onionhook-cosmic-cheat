#pragma once
#include "c_player.h"
#include "c_moving_object_position.h"

#include <vector>
#include <optional>

namespace onionhook {
	class c_world : public c_object_wrapper {
	public:
		c_world(jobject object, JNIEnv* env, c_game_instance* game)
			: c_object_wrapper(object, env, game) {
		};

		int get_num_entities();
		int get_num_players();

		c_player get_player(int i);
		c_entity get_entity(int i);

		std::vector<c_player> get_players();
		std::vector<c_entity> get_entities();

		std::vector<c_player> get_valid_players();

		std::optional<c_moving_object_position> ray_trace(vec3_t start, vec3_t end);

		inline bool is_valid() {
			return this->m_object;
		}
	};
}