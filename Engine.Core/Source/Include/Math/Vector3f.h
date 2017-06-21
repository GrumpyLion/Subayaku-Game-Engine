#pragma once

#include <cmath>
#include <stdio.h>

struct Vector3f
{
	float x = 0.0f, y = 0.0f, z = 0.0f;

	Vector3f()
	{ }

	Vector3f(float a_X, float a_Y, float a_Z)
		: x(a_X), y(a_Y), z(a_Z) {}
	
	Vector3f(float a_X, float a_Y)
		: x(a_X), y(a_Y), z(0.0f) {}

	Vector3f(float a_Val)
		: x(a_Val), y(a_Val), z(a_Val) {}

	Vector3f(const Vector3f &a_Vec)
		: x(a_Vec.x), y(a_Vec.y), z(a_Vec.z) {}

	inline void Print()
	{
		printf("%f, %f, %f\n", x, y, z);
	}

	inline void Set(const float &a_X, const float &a_Y, const float &a_Z)
	{
		x = a_X;
		y = a_Y;
		z = a_Z;
	}

	inline void Set(const Vector3f &a_Vec)
	{
		x = a_Vec.x;
		y = a_Vec.y;
		z = a_Vec.z;
	}

	inline void Translate(const float &a_X, const float &a_Y, const float &a_Z)
	{
		x += a_X;
		y += a_Y;
		z += a_Z;
	}

	inline void Translate(Vector3f a_Vec)
	{
		x += a_Vec.x;
		y += a_Vec.y;
		z += a_Vec.z;
	}

	inline void Scale(const float &a_X, const float &a_Y, const float &a_Z)
	{
		x *= a_X;
		y *= a_Y;
		z *= a_Z;
	}

	inline void Scale(const float &a_Amount)
	{
		x *= a_Amount;
		y *= a_Amount;
		z *= a_Amount;
	}

	inline void Scale(const Vector3f &a_Vec)
	{
		x *= a_Vec.x;
		y *= a_Vec.y;
		z *= a_Vec.z;
	}

	inline void Divide(const float &a_Amount)
	{
		x /= a_Amount;
		y /= a_Amount;
		z /= a_Amount;
	}

	inline void Divide(const Vector3f &a_Vec)
	{
		x /= a_Vec.x;
		y /= a_Vec.y;
		z /= a_Vec.z;
	}

	inline void Invert()
	{
		x *= -1;
		y *= -1;
		z *= -1;
	}

	inline void Normalize()
	{
		float len = Length();
		x /= len;
		y /= len;
		z /= len;
	}

	inline void Lerp(Vector3f a_To, float a_Amount)
	{
		*this += (a_To - *this) * a_Amount;
	}

	inline float Dot(const Vector3f &a_Vec)
	{	return x * a_Vec.x + y * a_Vec.y + z * a_Vec.z;	}

	inline float Length()
	{	return std::sqrt((x*x) + (y*y) + (z*z));	}

	inline static Vector3f Cross(const Vector3f a_Vec1, const Vector3f a_Vec2)
	{
		Vector3f temp;
		temp.x = a_Vec1.y * a_Vec2.z - a_Vec1.z * a_Vec2.y;
		temp.y = a_Vec1.z * a_Vec2.x - a_Vec1.x * a_Vec2.z;
		temp.z = a_Vec1.x * a_Vec2.y - a_Vec1.y * a_Vec2.x;
		return temp;
	}

	inline Vector3f &Vector3f::operator+=(const Vector3f &a_Vec)
	{
		Translate(a_Vec);
		return *this;
	}

	inline Vector3f &Vector3f::operator+(const Vector3f &a_Vec) const
	{
		Vector3f result = *this;
		result += a_Vec;
		return result;
	}

	inline Vector3f &Vector3f::operator-=(const Vector3f &a_Vec)
	{
		Vector3f temp = Vector3f(a_Vec);
		temp.Invert();
		Translate(temp);
		return *this;
	}

	inline Vector3f &Vector3f::operator-(const Vector3f &a_Vec) const
	{
		Vector3f result = *this;
		result -= a_Vec;
		return result;
	}

	inline Vector3f &Vector3f::operator/=(const Vector3f &a_Vec)
	{
		Divide(a_Vec);
		return *this;
	}

	inline Vector3f &Vector3f::operator/(const Vector3f &a_Vec) const
	{
		Vector3f result = *this;
		result /= a_Vec;
		return result;
	}

	inline Vector3f &Vector3f::operator*=(const Vector3f &a_Vec)
	{
		Scale(a_Vec);
		return *this;
	}

	inline Vector3f &Vector3f::operator*(const Vector3f &a_Vec) const
	{
		Vector3f result = *this;
		result *= a_Vec;
		return result;
	}

	inline Vector3f &Vector3f::operator*=(const float &a_Val)
	{
		Scale(a_Val);
		return *this;
	}

	inline Vector3f &Vector3f::operator*(const float &a_Val) const
	{
		Vector3f result = *this;
		result *= a_Val;
		return result;
	}

	inline bool operator==(const Vector3f& a_Other) const
	{
		return (x == a_Other.x &&
				y == a_Other.y &&
				z == a_Other.z);
	}
};