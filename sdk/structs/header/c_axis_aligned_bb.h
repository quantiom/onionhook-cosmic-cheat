#pragma once
#include "c_object_wrapper.h"

class vec3_t;

namespace onionhook {
	class c_game_instance;
	class c_axis_aligned_bb : public c_object_wrapper {
	public:
		c_axis_aligned_bb(jobject object, JNIEnv* env, c_game_instance* game)
			: c_object_wrapper(object, env, game) {
		}

		vec3_t get_min();
		vec3_t get_max();

		void set_min(vec3_t min);
		void set_max(vec3_t max);

		float get_min_x();
		float get_min_y();
		float get_min_z();

		float get_max_x();
		float get_max_y();
		float get_max_z();
	};
}