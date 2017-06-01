#pragma once

#include <cmath>
#include "Vector3f.h"
#include <stdio.h>

struct Vector4f
{
	float x = 0.0f, y = 0.0f, z = 0.0f, w = 1.0f;

	Vector4f()
	{ }

	Vector4f(float a_X, float a_Y, float a_Z, float a_W)
		: x(a_X), y(a_Y), z(a_Z), w(a_W) {}

	Vector4f(float a_Val)
		: x(a_Val), y(a_Val), z(a_Val), w(a_Val) {}

	Vector4f(const Vector3f &a_Vec)
		: x(a_Vec.x), y(a_Vec.y), z(a_Vec.z), w(1.0f) {}

	Vector4f(const Vector4f &a_Vec)
		: x(a_Vec.x), y(a_Vec.y), z(a_Vec.z), w(a_Vec.w) {}

	void Print()
	{
		printf("%f, %f, %f, %f\n", x, y, z, w);
	}

	void Set(const float &a_X, const float &a_Y, const float &a_Z, const float &a_W)
	{
		x = a_X;
		y = a_Y;
		z = a_Z;
		w = a_W;
	}

	void Set(const Vector4f &a_Vec)
	{
		x = a_Vec.x;
		y = a_Vec.y;
		z = a_Vec.z;
		w = a_Vec.w;
	}

	void Translate(const float &a_X, const float &a_Y, const float &a_Z, const float &a_W)
	{
		x += a_X;
		y += a_Y;
		z += a_Z;
		w += a_W;
	}

	void Translate(Vector4f a_Vec)
	{
		x += a_Vec.x;
		y += a_Vec.y;
		z += a_Vec.z;
		w += a_Vec.w;
	}

	void Scale(const float &a_X, const float &a_Y, const float &a_Z, const float &a_W)
	{
		x *= a_X;
		y *= a_Y;
		z *= a_Z;
		w *= a_W;
	}

	void Scale(const float &a_Amount)
	{
		x *= a_Amount;
		y *= a_Amount;
		z *= a_Amount;
		w *= a_Amount;
	}

	void Scale(const Vector4f &a_Vec)
	{
		x *= a_Vec.x;
		y *= a_Vec.y;
		z *= a_Vec.z;
		w *= a_Vec.w;
	}

	void Divide(const float &a_Amount)
	{
		x /= a_Amount;
		y /= a_Amount;
		z /= a_Amount;
		w /= a_Amount;
	}

	void Divide(const Vector4f &a_Vec)
	{
		x /= a_Vec.x;
		y /= a_Vec.y;
		z /= a_Vec.z;
		w /= a_Vec.w;
	}

	void Invert()
	{
		x *= -1;
		y *= -1;
		z *= -1;
		w *= -1;
	}

	void Normalize()
	{
		float len = Length();
		x /= len;
		y /= len;
		z /= len;
		w /= len;
	}

	float Dot(const Vector4f &a_Vec)
	{
		return x * a_Vec.x + y * a_Vec.y + z * a_Vec.z + w * a_Vec.w;
	}

	float Length()
	{
		return std::sqrt((x*x) + (y*y) + (z*z) + (w * w));
	}

	static Vector4f Cross(const Vector4f a_Vec1, const Vector4f a_Vec2)
	{
		Vector4f temp;
		temp.x = a_Vec1.y * a_Vec2.z - a_Vec1.z * a_Vec2.y;
		temp.y = a_Vec1.z * a_Vec2.x - a_Vec1.x * a_Vec2.z;
		temp.z = a_Vec1.x * a_Vec2.y - a_Vec1.y * a_Vec2.x;
		temp.w = 1.0f;
		return temp;
	}

	Vector4f &Vector4f::operator+=(const Vector4f &a_Vec)
	{
		Translate(a_Vec);
		return *this;
	}

	Vector4f &Vector4f::operator+(const Vector4f &a_Vec) const
	{
		Vector4f result = *this;
		result += a_Vec;
		return result;
	}

	Vector4f &Vector4f::operator-=(const Vector4f &a_Vec)
	{
		Vector4f temp = Vector4f(a_Vec);
		temp.Invert();
		Translate(temp);
		return *this;
	}

	Vector4f &Vector4f::operator-(const Vector4f &a_Vec) const
	{
		Vector4f result = *this;
		result -= a_Vec;
		return result;
	}

	Vector4f &Vector4f::operator/=(const Vector4f &a_Vec)
	{
		Divide(a_Vec);
		return *this;
	}

	Vector4f &Vector4f::operator/(const Vector4f &a_Vec) const
	{
		Vector4f result = *this;
		result /= a_Vec;
		return result;
	}

	Vector4f &Vector4f::operator*=(const Vector4f &a_Vec)
	{
		Scale(a_Vec);
		return *this;
	}

	Vector4f &Vector4f::operator*(const Vector4f &a_Vec) const
	{
		Vector4f result = *this;
		result *= a_Vec;
		return result;
	}

	Vector4f &Vector4f::operator*=(const float &a_Val)
	{
		Scale(a_Val);
		return *this;
	}

	Vector4f &Vector4f::operator*(const float &a_Val) const
	{
		Vector4f result = *this;
		result *= a_Val;
		return result;
	}
};