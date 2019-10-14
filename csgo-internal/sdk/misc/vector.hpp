#pragma once

#include <limits>

template <typename T>
T clip_number(const T& n, const T& lower, const T& upper)
{
	if (n < lower)
		return lower;

	if (n > upper)
		return upper;

	return n;
}


class vec3_t
{
public:
	vec3_t();
	vec3_t(float, float, float);
	~vec3_t();

	float x, y, z;

	vec3_t& operator+=(const vec3_t& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	vec3_t& operator-=(const vec3_t& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}

	vec3_t& operator*=(float v)
	{
		x *= v;
		y *= v;
		z *= v;

		return *this;
	}

	vec3_t operator+(const vec3_t& v)
	{
		return vec3_t{ x + v.x, y + v.y, z + v.z };
	}

	vec3_t operator-(const vec3_t& v)
	{
		return vec3_t{ x - v.x, y - v.y, z - v.z };
	}

	vec3_t operator*(float v) const
	{
		return vec3_t{ x * v, y * v, z * v };
	}

	float& operator[](int i)
	{
		return reinterpret_cast<float*>(this)[i];
	}

	float operator[](int i) const
	{
		return const_cast<float*>(reinterpret_cast<const float*>(this))[i];
	}

	void clamp();
	vec3_t normalized();
	void normalize();
	float length();
	float length_sqr();
	float dot(const vec3_t other);
};

typedef float matrix_t[3][4];


class vec2_t
{
public:
	float x, y;

	vec2_t()
	{
		x = 0;
		y = 0;
	};

	vec2_t(float X, float Y)
	{
		x = X;
		y = Y;
	};

	vec2_t(vec3_t vec)
	{
		x = vec.x;
		y = vec.y;
	}

	inline vec2_t operator*(const float n) const
	{
		return vec2_t(x * n, y * n);
	}

	inline vec2_t operator+(const vec2_t& v) const
	{
		return vec2_t(x + v.x, y + v.y);
	}

	inline vec2_t operator-(const vec2_t& v) const
	{
		return vec2_t(x - v.x, y - v.y);
	}

	inline void operator+=(const vec2_t& v)
	{
		x += v.x;
		y += v.y;
	}

	inline void operator-=(const vec2_t& v)
	{
		x -= v.x;
		y -= v.y;
	}

	bool operator==(const vec2_t& v) const
	{
		return (v.x == x && v.y == y);
	}

	bool operator!=(const vec2_t& v) const
	{
		return (v.x != x || v.y != y);
	}

	inline float length()
	{
		return sqrt((x * x) + (y * y));
	}
};
