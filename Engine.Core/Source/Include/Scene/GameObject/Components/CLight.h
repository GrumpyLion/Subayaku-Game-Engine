#pragma once

#include "Interface\IComponent.h"
#include "Math\Math.h"

namespace Scene
{
	enum ELightType
	{
		Directional,
		Point
	};

	class CLight : public IComponent
	{
	private:

	public:
		ELightType LightType;
		Vector4f Color;
		
		CLight(GameObject *a_Parent)
			: IComponent(a_Parent)
		{	}

		bool Initialize(Vector4f &a_Color, ELightType a_Type);

		void Update() final {	}
	};
}