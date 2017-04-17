#pragma once

#include "Interface\IComponent.h"

namespace Scene
{
	class CCamera : public IComponent
	{
	public:
		bool Initialize(GameObject *a_Parent) override;
		void Update() override;
		void Shutdown() override;
	};
}