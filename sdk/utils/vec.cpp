#include "vec.h"

// ================================================
//  constructors for vec3_t type
// ================================================

vec3_t::vec3_t(void) {
	x = y = z = 0.0f;
}

vec3_t::vec3_t(float fx, float fy, float fz) {
	x = fx;
	y = fy;
	z = fz;
}

vec3_t::vec3_t(vec2_t vec) {
	x = vec.x;
	y = vec.y;
}

vec3_t::~vec3_t(void) {};

// ================================================
//  constructors for vec2_t type
// ================================================

vec2_t::vec2_t(void) {
	x = y = 0.0f;
}

vec2_t::vec2_t(float fx, float fy) {
	x = fx;
	y = fy;
}

vec2_t::vec2_t(vec3_t vec) {
	x = vec.x;
	y = vec.y;
}

vec2_t::~vec2_t(void) {};

// ================================================
//  funcs for vec3_t type
// ================================================

vec3_t* vec3_t::clamp(void) {
	x = clip_number(std::remainder(x, 360.0f), -180.0f, 180.0f);
	y = clip_number(y, -89.0f, 89.0f);
	z = clip_number(z, -50.0f, 50.0f);

	return this;
}

void vec3_t::normalize(void) {
	auto vec_normalize = [&](vec3_t& v) {
		auto l = v.length();

		if (l != 0.0f) {
			v.x /= l;
			v.y /= l;
			v.z /= l;
		} else {
			v.x = v.y = 0.0f; v.z = 1.0f;
		}

		return l;
	};

	vec_normalize(*this);
}

vec3_t vec3_t::normalized(void) {
	vec3_t vec(*this);

	vec.normalize();

	return vec;
}

float vec3_t::normalize_in_place(void) {
	vec3_t& v = *this;

	float iradius = 1.f / (this->length() + 1.192092896e-07F); //FLT_EPSILON

	v.x *= iradius;
	v.y *= iradius;
	v.z *= iradius;

	return 1.f;
}

float vec3_t::distance_to(vec3_t& other) {
	vec3_t delta;
	delta.x = x - other.x;
	delta.y = y - other.y;
	delta.z = z - other.z;

	return delta.length();
}

float vec3_t::length(void) {
	return sqrt(this->length_sqr());
}

float vec3_t::length_2d(void) {
	return sqrt(this->y * this->y + this->x * this->x);
}

float vec3_t::length_sqr(void) {
	auto sqr = [](float n) {
		return static_cast<float>(n * n);
	};

	return (sqr(x) + sqr(y) + sqr(z));
}

vec3_t vec3_t::cross(vec3_t cross) {
	vec3_t result;
	result.x = y * cross.z - z * cross.y;
	result.y = z * cross.x - x * cross.z;
	result.z = x * cross.y - y * cross.x;
	return result;
}

// ================================================
//  funcs for vec2_t type
// ================================================

void vec2_t::clamp(void) {
	x = clip_number(x, -89.0f, 89.0f);
	y = clip_number(std::remainderf(y, 360.0f), -180.0f, 180.0f);
}

void vec2_t::normalize(void) {
	float length = this->length();

	if (length) {
		x /= length;
		y /= length;
	} else {
		x = y = 0.0f;
	}
}

vec2_t vec2_t::normalized(void) {
	vec2_t vec(*this);

	vec.normalize();

	return vec;
}

float vec2_t::length(void) {
	return sqrt(this->length_sqr());
}

float vec2_t::length_sqr(void) {
	auto sqr = [](float n) {
		return static_cast<float>(n * n);
	};

	return (sqr(x) + sqr(y));
}

vec4_t::vec4_t(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

vec4i_t::vec4i_t(int x, int y, int z, int w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
