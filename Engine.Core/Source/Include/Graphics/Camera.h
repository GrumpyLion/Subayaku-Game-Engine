#pragma once

#include "Scene\GameObject\Components\Transformation.h"

namespace Graphics
{
	class Camera
	{
	public:
		Matrix4f ToProjectionMatrixLH;
		Matrix4f ToProjectionMatrixRH;
		Matrix4f ToViewMatrixRH;
		Matrix4f ToViewMatrixLH;

		Scene::Transformation Transform;

		float FOV, Near, Far;

		Camera(float a_FOV, float a_Near, float a_Far)
			: FOV(a_FOV), Near(a_Near), Far(a_Far)
		{	}

		__declspec(dllexport) void UpdatePerspective(Scene::Transformation &a_Transform, float a_Width, float a_Height);
		__declspec(dllexport) void UpdateOrthographic(Scene::Transformation &a_Transform, float a_Left, float a_Right, float a_Top, float a_Bottom);
	};
}