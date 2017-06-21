#pragma once

#include <cmath>

struct Vector2f
{
	float x = 0.0f, y = 0.0f;

	Vector2f()
	{ }

	Vector2f(float a_X, float a_Y)
		: x(a_X), y(a_Y){}

	Vector2f(float a_Val)
		: x(a_Val), y(a_Val) {}

	Vector2f(const Vector2f &a_Vec)
		: x(a_Vec.x), y(a_Vec.y) {}

	inline void Set(const float &a_X, const float &a_Y)
	{
		x = a_X;
		y = a_Y;
	}

	inline void Set(const Vector2f &a_Vec)
	{
		x = a_Vec.x;
		y = a_Vec.y;
	}

	inline void Translate(const float &a_X, const float &a_Y)
	{
		x += a_X;
		y += a_Y;
	}

	inline void Translate(Vector2f a_Vec)
	{
		x += a_Vec.x;
		y += a_Vec.y;
	}

	inline void Scale(const float &a_X, const float &a_Y)
	{
		x *= a_X;
		y *= a_Y;
	}

	inline void Scale(const float &a_Amount)
	{
		x *= a_Amount;
		y *= a_Amount;
	}

	inline void Scale(const Vector2f &a_Vec)
	{
		x *= a_Vec.x;
		y *= a_Vec.y;
	}

	inline void Divide(const float &a_Amount)
	{
		x /= a_Amount;
		y /= a_Amount;
	}

	inline void Divide(const Vector2f &a_Vec)
	{
		x /= a_Vec.x;
		y /= a_Vec.y;
	}

	inline void Invert()
	{
		x *= -1;
		y *= -1;
	}

	inline void Normalize()
	{
		float len = Length();
		x /= len;
		y /= len;
	}

	inline void Lerp(Vector2f a_To, float a_Amount)
	{
		*this += (a_To - *this) * a_Amount;
	}

	inline float Dot(const Vector2f &a_Vec)
	{
		return x * a_Vec.x + y * a_Vec.y;
	}

	inline float Length()
	{
		return std::sqrt((x*x) + (y*y));
	}

	inline Vector2f &Vector2f::operator+=(const Vector2f &a_Vec)
	{
		Translate(a_Vec);
		return *this;
	}

	inline Vector2f &Vector2f::operator+(const Vector2f &a_Vec) const
	{
		Vector2f result = *this;
		result += a_Vec;
		return result;
	}

	inline Vector2f &Vector2f::operator-=(const Vector2f &a_Vec)
	{
		Vector2f temp = Vector2f(a_Vec);
		temp.Invert();
		Translate(temp);
		return *this;
	}

	inline Vector2f &Vector2f::operator-(const Vector2f &a_Vec) const
	{
		Vector2f result = *this;
		result -= a_Vec;
		return result;
	}

	inline Vector2f &Vector2f::operator/=(const Vector2f &a_Vec)
	{
		Divide(a_Vec);
		return *this;
	}

	inline Vector2f &Vector2f::operator/(const Vector2f &a_Vec) const
	{
		Vector2f result = *this;
		result /= a_Vec;
		return result;
	}

	inline Vector2f &Vector2f::operator*=(const Vector2f &a_Vec)
	{
		Scale(a_Vec);
		return *this;
	}

	inline Vector2f &Vector2f::operator*(const Vector2f &a_Vec) const
	{
		Vector2f result = *this;
		result *= a_Vec;
		return result;
	}

	inline Vector2f &Vector2f::operator*=(const float &a_Val)
	{
		Scale(a_Val);
		return *this;
	}

	inline Vector2f &Vector2f::operator*(const float &a_Val) const
	{
		Vector2f result = *this;
		result *= a_Val;
		return result;
	}

	inline bool operator==(const Vector2f& a_Other) const
	{
		return (x == a_Other.x &&
			y == a_Other.y);
	}
};