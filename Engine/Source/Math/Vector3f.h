#pragma once

#include <cmath>

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

	void Set(const float &a_X, const float &a_Y, const float &a_Z)
	{
		x = a_X;
		y = a_Y;
		z = a_Z;
	}

	void Set(const Vector3f &a_Vec)
	{
		x = a_Vec.x;
		y = a_Vec.y;
		z = a_Vec.z;
	}

	void Translate(const float &a_X, const float &a_Y, const float &a_Z)
	{
		x += a_X;
		y += a_Y;
		z += a_Z;
	}

	void Translate(Vector3f a_Vec)
	{
		x += a_Vec.x;
		y += a_Vec.y;
		z += a_Vec.z;
	}

	void Scale(const float &a_X, const float &a_Y, const float &a_Z)
	{
		x *= a_X;
		y *= a_Y;
		z *= a_Z;
	}

	void Scale(const float &a_Amount)
	{
		x *= a_Amount;
		y *= a_Amount;
		z *= a_Amount;
	}

	void Scale(const Vector3f &a_Vec)
	{
		x *= a_Vec.x;
		y *= a_Vec.y;
		z *= a_Vec.z;
	}

	void Divide(const float &a_Amount)
	{
		x /= a_Amount;
		y /= a_Amount;
		z /= a_Amount;
	}

	void Divide(const Vector3f &a_Vec)
	{
		x /= a_Vec.x;
		y /= a_Vec.y;
		z /= a_Vec.z;
	}

	void Invert()
	{
		x *= -1;
		y *= -1;
		z *= -1;
	}

	void Normalize()
	{
		float len = Length();
		x /= len;
		y /= len;
		z /= len;
	}

	float Dot(const Vector3f &a_Vec)
	{	return x * a_Vec.x + y * a_Vec.y + z * a_Vec.z;	}

	float Length()
	{	return std::sqrt((x*x) + (y*y) + (z*z));	}

	Vector3f &Vector3f::operator+=(const Vector3f &a_Vec)
	{
		Translate(a_Vec);
		return *this;
	}

	Vector3f &Vector3f::operator+(const Vector3f &a_Vec) const
	{
		Vector3f result = *this;
		result += a_Vec;
		return result;
	}

	Vector3f &Vector3f::operator-=(const Vector3f &a_Vec)
	{
		Vector3f temp = Vector3f(a_Vec);
		temp.Invert();
		Translate(temp);
		return *this;
	}

	Vector3f &Vector3f::operator-(const Vector3f &a_Vec) const
	{
		Vector3f result = *this;
		result -= a_Vec;
		return result;
	}

	Vector3f &Vector3f::operator/=(const Vector3f &a_Vec)
	{
		Divide(a_Vec);
		return *this;
	}

	Vector3f &Vector3f::operator/(const Vector3f &a_Vec) const
	{
		Vector3f result = *this;
		result /= a_Vec;
		return result;
	}

	Vector3f &Vector3f::operator*=(const Vector3f &a_Vec)
	{
		Scale(a_Vec);
		return *this;
	}

	Vector3f &Vector3f::operator*(const Vector3f &a_Vec) const
	{
		Vector3f result = *this;
		result *= a_Vec;
		return result;
	}

	Vector3f &Vector3f::operator*=(const float &a_Val)
	{
		Scale(a_Val);
		return *this;
	}

	Vector3f &Vector3f::operator*(const float &a_Val) const
	{
		Vector3f result = *this;
		result *= a_Val;
		return result;
	}
};