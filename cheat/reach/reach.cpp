#include "reach.h"
#include "../cheat.h"
#include "../../sdk/utils/math.h"
#include "../../sdk/structs/header/c_axis_aligned_bb.h"

#include <memory>

namespace onionhook::reach {
	void run() {
		static std::shared_ptr<c_onion_timer> timer = std::make_shared<c_onion_timer>();

		if (!timer->has_passed(25)) {
			return;
		}

		auto world = cheat::game->get_world();

		auto local_player = cheat::game->get_player();
		const auto local_pos = local_player.get_position();
		
		auto distance = 0.5f;

		for (auto player : world.get_valid_players()) {
			const auto pos = player.get_position();
			auto bounding_box = player.get_bounding_box();

			const auto min = bounding_box.get_min();
			const auto max = bounding_box.get_max();

			const auto hypothenuse_distance = hypot(local_pos.x - pos.x, local_pos.z - pos.z);

			if (distance > hypothenuse_distance)
				distance -= hypothenuse_distance;

			const auto angles = math::get_angles(local_pos, pos);
			const auto difference = math::wrap_to_180(-(local_player.get_yaw() - angles.first));

			if (std::abs(difference) > 180.0f)
				continue;

			const auto cos = std::cos(math::deg_to_radiants(angles.first + 90.0f));
			const auto sin = std::sin(math::deg_to_radiants(angles.first + 90.0f));

			auto x = pos.x, z = pos.z;
			x -= (cos * distance);
			z -= (sin * distance);

			const static auto entity_width = 0.6f;
			const auto bb_width = entity_width / 2.0f;

			auto current_bounding_box = player.get_bounding_box();

			current_bounding_box.set_min({ x - bb_width, current_bounding_box.get_min_y(), z - bb_width });
			current_bounding_box.set_max({ x + bb_width, current_bounding_box.get_max_y(), z + bb_width });
		
			current_bounding_box.free();
			player.free();
			bounding_box.free();
		}

		local_player.free();
		world.free();

		timer->reset();
	}
}