#pragma once

#include "Math\Math.h"

namespace Scene
{
	class Transformation
	{
	public:
		Vector3f Position;
		Vector3f Scale = Vector3f(1,1,1);
		Vector3f Rotation;

		Matrix4f ToWorldMatrix()
		{
			Matrix4f temp = Matrix4f::Identity();
			temp *= Matrix4f::Translate(Position);
			temp *= Matrix4f::Scale(Scale);
			temp *= Matrix4f::RotateX(Rotation.x * DEGTORAD);
			temp *= Matrix4f::RotateY(Rotation.y * DEGTORAD);
			temp *= Matrix4f::RotateZ(Rotation.z * DEGTORAD);
			return temp;
		}
	};
}