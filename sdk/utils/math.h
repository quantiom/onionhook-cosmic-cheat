#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include "vec.h"

namespace onionhook::math {
	inline float wrap_to_180(float value) {
		if (value >= 180.f)
			value -= 360.f;
		if (value < -180.f)
			value += 360.f;
		return value;
	}

	inline float radiants_to_deg(float x) {
		return x * 180.f / M_PI;
	}

	inline float deg_to_radiants(float r) {
		return r * M_PI / 180;
	}

	inline std::pair<float, float> get_angles(vec3_t pos, vec3_t pos1) {
		float d_x = pos1.x - pos.x;
		float d_y = pos1.y - pos.y;
		float d_z = pos1.z - pos.z;

		float hypothenuse = sqrt(d_x * d_x + d_z * d_z);
		float yaw = radiants_to_deg(atan2(d_z, d_x)) - 90.f;
		float pitch = radiants_to_deg(-atan2(d_y, hypothenuse));

		return std::make_pair(yaw, pitch);
	}

	inline void vector_angles(vec3_t& forward, vec3_t& angles) {
		auto yaw = atan2(forward.z, forward.x) + M_PI / 2.0f;
		auto pitch = atan2(forward.y, sqrt(forward.z * forward.z + forward.x * forward.x));

		angles.x = radiants_to_deg(yaw);
		angles.y = radiants_to_deg(pitch);
		angles.z = 0.0f;
	}

	inline vec3_t calculate_angle(vec3_t& a, vec3_t& b) {
		vec3_t angles;

		vec3_t delta = a - b;

		vector_angles(delta, angles);

		return angles;
	}
}