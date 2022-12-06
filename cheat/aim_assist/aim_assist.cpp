#include "../cheat.h"
#include "../../sdk/utils/math.h"
#include "../../sdk/input/input.h"
#include "aim_assist.h"

namespace onionhook::aim_assist {
	namespace config {
		inline bool enabled = true;
		inline float fov = 40.0f;
		inline float smoothing = 10.0f;
		inline float range = 5.0f;
		inline bool aim_at_head = false;
		inline bool enemy_only = true;
		inline int key = VK_LBUTTON;
	}

	void run() {
		if (config::enabled && (input::get_key_state(config::key) == input::keystate::held || input::get_key_state(config::key) == input::keystate::pressed) && cheat::game->has_focus()) {
			auto best_player = get_best_player();

			if (best_player.has_value() && best_player->is_valid()) {
				auto local_player = cheat::game->get_player();

				auto local_player_pos = local_player.get_position();
				auto best_player_pos = best_player->get_position();

				if (!config::aim_at_head) best_player_pos.y -= 0.5f;

				auto local_angles = local_player.get_angles();
				local_angles.clamp();

				auto enemy_angles = math::calculate_angle(local_player_pos, best_player_pos);
				enemy_angles.clamp();

				auto delta = local_angles - enemy_angles;
				delta.clamp();

				auto final_angles = local_angles - delta / vec3_t{ config::smoothing * 20.f, config::smoothing * 20.f, 0 };

				local_player.set_angles(final_angles);

				local_player.free();
			}
		}
	}

	std::optional<c_player> get_best_player() {
		c_player best_player{ nullptr, nullptr, nullptr };
		float best_fov = INT_MAX;

		auto local_player = cheat::game->get_player();
		auto local_player_pos = local_player.get_position();
		auto eye_pos = local_player.get_eye_position().to_vec3();

		auto local_angles = local_player.get_angles();
		local_angles.clamp();

		for (auto enemy : cheat::game->get_world().get_valid_players()) {
			auto enemy_pos = enemy.get_position();

			if (local_player_pos.distance_to(enemy_pos) > config::range) continue;
			//if (config::combat::aim_assist::enemy_only && !enemy.is_neutral_or_enemy()) continue;

			auto ray_info = cheat::game->get_world().ray_trace(eye_pos, enemy.get_eye_position().to_vec3());

			if (!ray_info.has_value() || !ray_info->is_valid() || ray_info->get_type_of_hit() != c_moving_object_position::hit_type::entity) {
				if (ray_info.has_value()) {
					ray_info->free();
				}

				continue;
			}

			ray_info->free();

			auto enemy_angles = math::calculate_angle(local_player_pos, enemy_pos);
			enemy_angles.clamp();

			auto delta = local_angles - enemy_angles;
			delta.clamp();

			const auto fov = delta.length_2d();

			if (fov < config::fov && fov < best_fov) {
				best_fov = fov;
				best_player = enemy;
			} else {
				enemy.free();
			}
		}

		if (best_fov == INT_MAX) return {};
		return best_player;
	}
}