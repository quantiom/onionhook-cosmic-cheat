#pragma once
#include "c_object_wrapper.h"

class vec3_t;

namespace onionhook {
	class c_minecraft_vector;
	class c_axis_aligned_bb;
	
	class c_entity : public c_object_wrapper {
	public:
		c_entity(jobject javaclass, JNIEnv* env, c_game_instance* game)
			: c_object_wrapper(javaclass, env, game) {
		};

		int get_id();
		int get_health();

		bool is_alive();
		bool is_valid();
		
		vec3_t get_angles();
		vec3_t get_prev_angles();

		void set_angles(vec3_t angles);

		vec3_t get_position();
		c_minecraft_vector get_eye_position();

		c_axis_aligned_bb get_bounding_box();

		float get_yaw();
		float get_pitch();

		float get_prev_yaw();
		float get_prev_pitch();

		float get_x();
		float get_y();
		float get_z();
	};
}