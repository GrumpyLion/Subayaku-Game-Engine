#include "Scene\GameObject\Components\CCamera.h"

#include "Graphics\Interfaces\IRenderer.h"
#include "Input\InputManager.h"
#include "Scene\GameObject\GameObject.h"

namespace Scene
{
	CCamera::~CCamera()
	{
		Core::SEventDesc eventDesc{};

		eventDesc.Event = Core::EEvents::SCENE_CAMERACOMPONENT_REMOVED;
		Core::EventHandler::StaticClass()->AddEvent(eventDesc);
	}

	CCamera::CCamera(GameObject *a_Parent)
		: IComponent(a_Parent)
	{
		Type = ComponentType::Camera;
	}

	bool CCamera::Initialize(float a_FOV, float a_Near, float a_Far)
	{
		m_Camera = std::make_unique<Graphics::Camera>(a_FOV, a_Near, a_Far);

		CurrentCamera = true;

		Core::SEventDesc eventDesc{};

		eventDesc.Event = Core::EEvents::SCENE_CAMERACOMPONENT_ADDED;
		eventDesc.Description = this;

		Core::EventHandler::StaticClass()->AddEvent(eventDesc);
		
		return true;
	}

	void CCamera::Update()
	{
		m_Camera->UpdatePerspective(*Parent->Transform, (float)Core::Engine::StaticClass()->GetContext().Width, (float)Core::Engine::StaticClass()->GetContext().Height);
	}
}