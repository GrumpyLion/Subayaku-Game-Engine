#pragma once

#include "Interface\IComponent.h"
#include "Scene\GameObject\GameObject.h"
#include "Math\Math.h"

namespace Scene
{
	class CCamera : public IComponent
	{
	public:
		~CCamera();

		float FOV, Near, Far;
		bool CurrentCamera = false;
		
		bool Initialize(GameObject *a_Parent, float a_FOV, float a_Near, float a_Far);
		void Update() override;

		Matrix4f ToProjectionMatrixLH();
		Matrix4f ToProjectionMatrixRH();
		Matrix4f ToViewMatrixRH();
		Matrix4f ToViewMatrixLH();
	};
}