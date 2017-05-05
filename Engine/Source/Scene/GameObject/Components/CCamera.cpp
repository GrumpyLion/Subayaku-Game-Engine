#include "CCamera.h"
#include "Core\Engine.h"
#include "Scene\Scene.h"
#include "Graphics\Interface\IRenderer.h"
#include "Scene\GameObject\GameObject.h"
#include "Input\Keyboard.h"
#include "Scene\GameObject\Components\Transformation.h"

namespace Scene
{
	bool CCamera::Initialize(GameObject *a_Parent, float a_FOV, float a_Near, float a_Far)
	{
		IComponent::Initialize(a_Parent);
		FOV = a_FOV;
		Near = a_Near;
		Far = a_Far;

		Core::Engine::StaticClass()->GetRenderer()->SetCamera(this);
		Core::Engine::StaticClass()->GetScene()->SetCamera(this);

		return true;
	}

	void CCamera::Update()
	{
		if (Core::Engine::StaticClass()->GetKeyboard()->IsKeyDown(SUBA_KEY_W))
		{
			Parent->Transform->Rotation.x++;
		}

		if (Core::Engine::StaticClass()->GetKeyboard()->IsKeyDown(SUBA_KEY_A))
		{
			Parent->Transform->Rotation.y--;
		}

		if (Core::Engine::StaticClass()->GetKeyboard()->IsKeyDown(SUBA_KEY_S))
		{
			Parent->Transform->Rotation.x--;
		}

		if (Core::Engine::StaticClass()->GetKeyboard()->IsKeyDown(SUBA_KEY_D))
		{
			Parent->Transform->Rotation.y++;
		}

		if (Core::Engine::StaticClass()->GetKeyboard()->IsKeyDown(SUBA_KEY_E))
		{
			m_Radius++;
		}

		if (Core::Engine::StaticClass()->GetKeyboard()->IsKeyDown(SUBA_KEY_Q))
		{
			m_Radius--;
		}

		float xOffset = CalculateHorizontalDistance() * std::sin(Parent->Transform->Rotation.y * DEGTORAD);
		float zOffset = CalculateHorizontalDistance() * std::cos(Parent->Transform->Rotation.y * DEGTORAD);

		Parent->Transform->Position.x = -xOffset;
		Parent->Transform->Position.y = CalculateVerticalDistance();
		Parent->Transform->Position.z = zOffset;
	}

	float CCamera::CalculateHorizontalDistance()
	{
		return -m_Radius * std::cos(Parent->Transform->Rotation.x * DEGTORAD);
	}

	float CCamera::CalculateVerticalDistance()
	{
		return -m_Radius * std::sin(Parent->Transform->Rotation.x * DEGTORAD);
	}

	void CCamera::Shutdown()
	{
		Core::Engine::StaticClass()->GetRenderer()->SetCamera(nullptr);
	}
}