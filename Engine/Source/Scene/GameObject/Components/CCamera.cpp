#include "CCamera.h"
#include "Core\Engine.h"
#include "Scene\Scene.h"
#include "Graphics\Interface\IRenderer.h"

namespace Scene
{
	bool CCamera::Initialize(GameObject *a_Parent)
	{
		IComponent::Initialize(a_Parent);
		FOV = 60.0f;
		Near = 0.1f;
		Far = 500.0f;

		Core::Engine::StaticClass()->GetRenderer()->SetCamera(this);
		Core::Engine::StaticClass()->GetScene()->SetCamera(this);

		return true;
	}

	void CCamera::Update()
	{

	}

	void CCamera::Shutdown()
	{
		Core::Engine::StaticClass()->GetRenderer()->SetCamera(nullptr);
	}
}