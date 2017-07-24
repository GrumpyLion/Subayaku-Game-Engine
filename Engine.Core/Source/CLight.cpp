#include "Scene\GameObject\Components\CLight.h"

#include "Utilities\Event\SEventDesc.h"
#include "Utilities\Event\EventHandler.h"

namespace Scene
{
	bool CLight::Initialize(Vector4f &a_Color, ELightType a_Type)
	{
		Type = ComponentType::Light;
		Color = a_Color;
		LightType = a_Type;

		Core::SEventDesc eventDesc{};
		eventDesc.Event = Core::EEvents::SCENE_LIGHT_ADDED;
		eventDesc.Description = this;
		Core::EventHandler::StaticClass()->AddEvent(eventDesc);

		return true;
	}
}