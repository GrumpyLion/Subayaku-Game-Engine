#pragma once

#include "Interface\IComponent.h"

namespace Scene
{
	class CCamera : public IComponent
	{
	public:
		float FOV, Near, Far;
		
		bool Initialize(GameObject *a_Parent, float a_FOV, float a_Near, float a_Far);
		void Update() override;
		void Shutdown() override;

		//Delete later ..
		float m_Radius = 350.0f;
		float CalculateHorizontalDistance();
		float CalculateVerticalDistance();
	};
}