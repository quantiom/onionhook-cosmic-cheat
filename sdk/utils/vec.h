#pragma once
#include "../includes.h"

// ======================================================
//  positioning classes
// ======================================================

// std libs being retarded, just use this
template <typename T>
T clip_number(const T& n, const T& lower, const T& upper) {
	return max(lower, min(n, upper));
}

typedef float matrix_t[3][4];

class vec4_t {
public:
	vec4_t(float, float, float, float);

	float x, y, z, w;
};

class vec4i_t {
public:
	vec4i_t(int, int, int, int);

	int x, y, z, w;
};

class vec2_t;
class vec3_t {
public:
	vec3_t();
	vec3_t(vec2_t);
	vec3_t(float, float, float);
	~vec3_t();

	float x, y, z; // 12 bytes total

	vec3_t& operator+=(const vec3_t& v) {
		x += v.x; y += v.y; z += v.z; return *this;
	}

	vec3_t& operator-=(const vec3_t& v) {
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}

	vec3_t& operator*=(float v) {
		x *= v; y *= v; z *= v; return *this;
	}

	vec3_t& operator/=(float v) {
		x /= v; y /= v; z /= v; return *this;
	}

	vec3_t operator/(const vec3_t& v) {
		return vec3_t{ x / v.x, y / v.y, z / v.z };
	}

	vec3_t operator-(const vec3_t& v) {
		return vec3_t{ x - v.x, y - v.y, z - v.z };
	}

	vec3_t operator+(const vec3_t& v) {
		return vec3_t{ x + v.x, y + v.y, z + v.z };
	}

	vec3_t operator*(float v) const {
		return vec3_t{ x * v, y * v, z * v };
	}

	friend std::ostream& operator<<(std::ostream& os, const vec3_t& vec) {
		os << "(x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z << ")";
		return os;
	}

	vec3_t* clamp();
	vec3_t normalized();
	float normalize_in_place();
	float distance_to(vec3_t& other);
	void normalize();
	float length();
	float length_2d();
	float length_sqr();
	vec3_t cross(vec3_t cross);
};

class vec2_t {
public:
	vec2_t();
	vec2_t(vec3_t);
	vec2_t(float, float);
	~vec2_t();

	float x, y; // 8 bytes total

	vec2_t& operator+=(const vec2_t& v) {
		x += v.x; y += v.y; return *this;
	}

	vec2_t& operator-=(const vec2_t& v) {
		x -= v.x; y -= v.y; return *this;
	}

	vec2_t& operator*=(float v) {
		x *= v; y *= v; return *this;
	}

	vec2_t operator-(const vec2_t& v) {
		return vec2_t{ x - v.x, y - v.y };
	}

	vec2_t operator+(const vec2_t& v) {
		return vec2_t{ x + v.x, y + v.y };
	}

	vec2_t operator*(float v) const {
		return vec2_t{ x * v, y * v };
	}

	void clamp();
	vec2_t normalized();
	void normalize();
	float length();
	float length_sqr();
};
