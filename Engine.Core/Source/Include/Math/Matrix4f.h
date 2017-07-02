#pragma once

#include "Vector3f.h"
#include <cmath>
#include <stdio.h>

#define PI 3.141593f
#define DEGTORAD PI / 180.0f

struct Matrix4f
{
	float m11 = 0, m12 = 0, m13 = 0, m14 = 0,
		m21 = 0, m22 = 0, m23 = 0, m24 = 0,
		m31 = 0, m32 = 0, m33 = 0, m34 = 0,
		m41 = 0, m42 = 0, m43 = 0, m44 = 0;

	Matrix4f()
	{
		m11 = 1.0f;
		m22 = 1.0f;
		m33 = 1.0f;
		m44 = 1.0f;
	}

	inline void Print()
	{
		printf("%f, %f, %f, %f,\n%f, %f, %f, %f,\n%f, %f, %f, %f,\n%f, %f, %f, %f\n",
			m11, m12, m13, m14,
			m21, m22, m23, m24,
			m31, m32, m33, m34,
			m41, m42, m43, m44);
	}

	inline void SetData(float *a_Data)
	{
		m11 = a_Data[0];
		m12 = a_Data[1];
		m13 = a_Data[2];
		m14 = a_Data[3];
		
		m21 = a_Data[4];
		m22 = a_Data[5];
		m23 = a_Data[6];
		m24 = a_Data[7];
		
		m31 = a_Data[8];
		m32 = a_Data[9];
		m33 = a_Data[10];
		m34 = a_Data[11];
		
		m41 = a_Data[12];
		m42 = a_Data[13];
		m43 = a_Data[14];
		m44 = a_Data[15];
	}

	inline void SetData(const Matrix4f a_Matrix)
	{
		m11 = a_Matrix.m11;
		m12 = a_Matrix.m12;
		m13 = a_Matrix.m13;
		m14 = a_Matrix.m14;

		m21 = a_Matrix.m21;
		m22 = a_Matrix.m22;
		m23 = a_Matrix.m23;
		m24 = a_Matrix.m24;

		m31 = a_Matrix.m31;
		m32 = a_Matrix.m32;
		m33 = a_Matrix.m33;
		m34 = a_Matrix.m34;

		m41 = a_Matrix.m41;
		m42 = a_Matrix.m42;
		m43 = a_Matrix.m43;
		m44 = a_Matrix.m44;
	}

	//Changes the Layout
	inline void Transpose()
	{
		float temp[16]
		{
			m11, m21, m31, m41,
			m12, m22, m32, m42,
			m13, m23, m33, m43,
			m14, m24, m34, m44
		};
		SetData(temp);
	}

	inline static Matrix4f Identity()
	{
		Matrix4f temp = Matrix4f();
		float mat[4 * 4]
		{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		temp.SetData(mat);
		return temp;
	}

	inline static Matrix4f Translate(float a_X, float a_Y, float a_Z)
	{
		return Translate(Vector3f(a_X, a_Y, a_Z));
	}

	inline static Matrix4f Translate(Vector3f a_Position)
	{
		float temp[16]
		{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			a_Position.x, a_Position.y, a_Position.z, 1.0f
		};
		Matrix4f mat = Matrix4f();
		mat.SetData(temp);
		return mat;
	}


	inline static Matrix4f RotateX(float a_Amount)
	{
		float temp[16]
		{
			1.0f, 0.0, 0.0, 0.0,
			0.0, std::cos(a_Amount), std::sin(a_Amount), 0.0,
			0.0, -std::sin(a_Amount), std::cos(a_Amount), 0.0,
			0.0, 0.0, 0.0, 1.0f
		};
		Matrix4f mat = Matrix4f();
		mat.SetData(temp);
		return mat;
	}

	inline static Matrix4f RotateY(float a_Amount)
	{
		float temp[16]
		{
			std::cos(a_Amount) , 0.0, -std::sin(a_Amount), 0.0,
			0.0, 1.0f, 0.0, 0.0,
			std::sin(a_Amount), 0.0, std::cos(a_Amount), 0.0,
			0.0, 0.0, 0.0, 1.0f
		};
		Matrix4f mat = Matrix4f();
		mat.SetData(temp);
		return mat;
	}

	inline static Matrix4f RotateZ(float a_Amount)
	{
		float temp[16]
		{
			std::cos(a_Amount), -std::sin(a_Amount), 0.0, 0.0,
			std::sin(a_Amount), std::cos(a_Amount), 0.0, 0.0,
			0.0, 0.0, 1.0f, 0.0,
			0.0, 0.0, 0.0, 1.0f
		};
		Matrix4f mat = Matrix4f();
		mat.SetData(temp);
		return mat;
	}

	inline static Matrix4f Scale(float a_X, float a_Y, float a_Z)
	{
		return Scale(Vector3f(a_X, a_Y, a_Z));
	}

	inline static Matrix4f Scale(Vector3f a_Scale)
	{
		float temp[16]
		{
			a_Scale.x, 0.0, 0.0, 0.0,
			0.0, a_Scale.y, 0.0, 0.0,
			0.0, 0.0, a_Scale.z, 0.0,
			0.0, 0.0, 0.0, 1.0f
		};
		Matrix4f mat = Matrix4f();
		mat.SetData(temp);
		return mat;
	}

	inline static Matrix4f PerspectiveRH(float a_FOV, float a_Aspect, float a_Near, float a_Far)
	{
		float yScale = 1.0f / std::tan(DEGTORAD * a_FOV / 2.0f);
		float xScale = yScale / a_Aspect;
		float NearFar = a_Far - a_Near;

		float temp[4 * 4]
		{
			xScale, 0.0f, 0.0f, 0.0f,
			0.0f, yScale, 0.0f, 0.0f,
			0.0f, 0.0f, a_Far / NearFar, 1,
			0.0f, 0.0f, a_Far*a_Near / (a_Near - a_Far), 0
		};

		Matrix4f mat = Matrix4f();
		mat.SetData(temp);
		return mat;
	}

	inline static Matrix4f PerspectiveLH(float a_FOV, float a_Aspect, float a_Near, float a_Far)
	{
		float yScale = 1.0f / std::tan(DEGTORAD * a_FOV / 2.0f);
		float xScale = yScale / a_Aspect;
		float NearFar = a_Far - a_Near;

		float temp[4 * 4]
		{
			xScale, 0.0f, 0.0f, 0.0f,
			0.0f, yScale, 0.0f, 0.0f,
			0.0f, 0.0f, a_Far / NearFar, 1,
			0.0f, 0.0f, a_Far*a_Near / (a_Near - a_Far), 0
		};

		Matrix4f mat = Matrix4f();
		mat.SetData(temp);
		return mat;
	}

	inline static Matrix4f Orthograpic(float a_Left, float a_Right, float a_Top, float a_Bottom, float a_Near, float a_Far)
	{
		float temp[4 * 4]
		{
			2 / (a_Right - a_Left), 0.0f, 0.0f, -(a_Right + a_Left) / (a_Right - a_Left),
			0.0f, 2 / (a_Top - a_Bottom), 0.0f, -(a_Top + a_Bottom) / (a_Top - a_Bottom),
			0.0f, 0.0f, 1 / (a_Far - a_Near),  -(a_Near)   / (a_Far - a_Near), 
			0.0f, 0.0f, 0.0f, 1.0f
		};

		Matrix4f mat = Matrix4f();
		mat.SetData(temp);
		mat.Transpose();
		return mat;
	}

	inline void Multiply(const Matrix4f &a_Matrix)
	{
		Matrix4f temp = Identity();
		temp.m11 = m11 * a_Matrix.m11 + m21 * a_Matrix.m12 + m31 * a_Matrix.m13 + m41 * a_Matrix.m14;
		temp.m12 = m12 * a_Matrix.m11 + m22 * a_Matrix.m12 + m32 * a_Matrix.m13 + m42 * a_Matrix.m14;
		temp.m13 = m13 * a_Matrix.m11 + m23 * a_Matrix.m12 + m33 * a_Matrix.m13 + m43 * a_Matrix.m14;
		temp.m14 = m14 * a_Matrix.m11 + m24 * a_Matrix.m12 + m34 * a_Matrix.m13 + m44 * a_Matrix.m14;

		temp.m21 = m11 * a_Matrix.m21 + m21 * a_Matrix.m22 + m31 * a_Matrix.m23 + m41 * a_Matrix.m24;
		temp.m22 = m12 * a_Matrix.m21 + m22 * a_Matrix.m22 + m32 * a_Matrix.m23 + m42 * a_Matrix.m24;
		temp.m23 = m13 * a_Matrix.m21 + m23 * a_Matrix.m22 + m33 * a_Matrix.m23 + m43 * a_Matrix.m24;
		temp.m24 = m14 * a_Matrix.m21 + m24 * a_Matrix.m22 + m34 * a_Matrix.m23 + m44 * a_Matrix.m24;

		temp.m31 = m11 * a_Matrix.m31 + m21 * a_Matrix.m32 + m31 * a_Matrix.m33 + m41 * a_Matrix.m34;
		temp.m32 = m12 * a_Matrix.m31 + m22 * a_Matrix.m32 + m32 * a_Matrix.m33 + m42 * a_Matrix.m34;
		temp.m33 = m13 * a_Matrix.m31 + m23 * a_Matrix.m32 + m33 * a_Matrix.m33 + m43 * a_Matrix.m34;
		temp.m34 = m14 * a_Matrix.m31 + m24 * a_Matrix.m32 + m34 * a_Matrix.m33 + m44 * a_Matrix.m34;

		temp.m41 = m11 * a_Matrix.m41 + m21 * a_Matrix.m42 + m31 * a_Matrix.m43 + m41 * a_Matrix.m44;
		temp.m42 = m12 * a_Matrix.m41 + m22 * a_Matrix.m42 + m32 * a_Matrix.m43 + m42 * a_Matrix.m44;
		temp.m43 = m13 * a_Matrix.m41 + m23 * a_Matrix.m42 + m33 * a_Matrix.m43 + m43 * a_Matrix.m44;
		temp.m44 = m14 * a_Matrix.m41 + m24 * a_Matrix.m42 + m34 * a_Matrix.m43 + m44 * a_Matrix.m44;
		
		SetData(temp);
	}

	inline Matrix4f &Matrix4f::operator*=(const Matrix4f &a_MatrixLeft)
	{
		Multiply(a_MatrixLeft);
		return *this;
	}

	inline Matrix4f &Matrix4f::operator* (Matrix4f &a_MatrixLeft) const
	{
		Matrix4f mat = *this;
		mat *= a_MatrixLeft;
		return mat;
	}
};