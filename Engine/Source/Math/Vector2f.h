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

	void Set(const float &a_X, const float &a_Y)
	{
		x = a_X;
		y = a_Y;
	}

	void Set(const Vector2f &a_Vec)
	{
		x = a_Vec.x;
		y = a_Vec.y;
	}

	void Translate(const float &a_X, const float &a_Y)
	{
		x += a_X;
		y += a_Y;
	}

	void Translate(Vector2f a_Vec)
	{
		x += a_Vec.x;
		y += a_Vec.y;
	}

	void Scale(const float &a_X, const float &a_Y)
	{
		x *= a_X;
		y *= a_Y;
	}

	void Scale(const float &a_Amount)
	{
		x *= a_Amount;
		y *= a_Amount;
	}

	void Scale(const Vector2f &a_Vec)
	{
		x *= a_Vec.x;
		y *= a_Vec.y;
	}

	void Divide(const float &a_Amount)
	{
		x /= a_Amount;
		y /= a_Amount;
	}

	void Divide(const Vector2f &a_Vec)
	{
		x /= a_Vec.x;
		y /= a_Vec.y;
	}

	void Invert()
	{
		x *= -1;
		y *= -1;
	}

	void Normalize()
	{
		float len = Length();
		x /= len;
		y /= len;
	}

	float Dot(const Vector2f &a_Vec)
	{
		return x * a_Vec.x + y * a_Vec.y;
	}

	float Length()
	{
		return std::sqrt((x*x) + (y*y));
	}

	Vector2f &Vector2f::operator+=(const Vector2f &a_Vec)
	{
		Translate(a_Vec);
		return *this;
	}

	Vector2f &Vector2f::operator+(const Vector2f &a_Vec) const
	{
		Vector2f result = *this;
		result += a_Vec;
		return result;
	}

	Vector2f &Vector2f::operator-=(const Vector2f &a_Vec)
	{
		Vector2f temp = Vector2f(a_Vec);
		temp.Invert();
		Translate(temp);
		return *this;
	}

	Vector2f &Vector2f::operator-(const Vector2f &a_Vec) const
	{
		Vector2f result = *this;
		result -= a_Vec;
		return result;
	}

	Vector2f &Vector2f::operator/=(const Vector2f &a_Vec)
	{
		Divide(a_Vec);
		return *this;
	}

	Vector2f &Vector2f::operator/(const Vector2f &a_Vec) const
	{
		Vector2f result = *this;
		result /= a_Vec;
		return result;
	}

	Vector2f &Vector2f::operator*=(const Vector2f &a_Vec)
	{
		Scale(a_Vec);
		return *this;
	}

	Vector2f &Vector2f::operator*(const Vector2f &a_Vec) const
	{
		Vector2f result = *this;
		result *= a_Vec;
		return result;
	}

	Vector2f &Vector2f::operator*=(const float &a_Val)
	{
		Scale(a_Val);
		return *this;
	}

	Vector2f &Vector2f::operator*(const float &a_Val) const
	{
		Vector2f result = *this;
		result *= a_Val;
		return result;
	}
};