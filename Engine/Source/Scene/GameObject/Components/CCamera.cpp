#include "CCamera.h"
#include "Core\Engine.h"
#include "Scene\Scene.h"
#include "Graphics\Interface\IRenderer.h"
#include "Scene\GameObject\GameObject.h"
#include "Input\InputManager.h"
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
		if (Core::Engine::StaticClass()->GetInputManager()->GetKeyboard()->IsKeyDown(SUBA_KEY_E))
		{
			m_Radius++;
		}

		if (Core::Engine::StaticClass()->GetInputManager()->GetKeyboard()->IsKeyDown(SUBA_KEY_Q))
		{
			m_Radius--;
		}

		if (Core::Engine::StaticClass()->GetInputManager()->GetMouse()->LeftButton)
		{
			xSpeed += Core::Engine::StaticClass()->GetInputManager()->GetMouse()->xD * 0.025f;
			ySpeed += Core::Engine::StaticClass()->GetInputManager()->GetMouse()->yD * 0.025f;
		}

		xSpeed *= 0.9f;
		ySpeed *= 0.9f;

		Parent->Transform->Rotation.y += xSpeed;
		Parent->Transform->Rotation.x -= ySpeed;

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

	Matrix4f CCamera::ToProjectionMatrixRH()
	{
		float aspect = (float)Core::Engine::StaticClass()->GetContext().Width / (float)Core::Engine::StaticClass()->GetContext().Height;
		return Matrix4f::PerspectiveRH(FOV,
			aspect, Near, Far);
	}

	Matrix4f CCamera::ToProjectionMatrixLH()
	{
		float aspect = (float)Core::Engine::StaticClass()->GetContext().Width / (float)Core::Engine::StaticClass()->GetContext().Height;
		return Matrix4f::PerspectiveLH(FOV,
			aspect, Near, Far);
	}

	Matrix4f CCamera::ToViewMatrixRH()
	{
		Matrix4f temp = Matrix4f::Identity();
		temp *= Matrix4f::RotateX(Parent->Transform->Rotation.x * DEGTORAD);
		temp *= Matrix4f::RotateY(Parent->Transform->Rotation.y * DEGTORAD);
		temp *= Matrix4f::RotateZ(Parent->Transform->Rotation.z * DEGTORAD);
		temp *= Matrix4f::Translate(Parent->Transform->Position);
		return temp;
	}

	Matrix4f CCamera::ToViewMatrixLH()
	{
		Matrix4f temp = Matrix4f::Identity();
		temp *= Matrix4f::RotateX(-Parent->Transform->Rotation.x * DEGTORAD);
		temp *= Matrix4f::RotateY(Parent->Transform->Rotation.y * DEGTORAD);
		temp *= Matrix4f::RotateZ(Parent->Transform->Rotation.z * DEGTORAD);
		temp *= Matrix4f::Translate(Parent->Transform->Position * Vector3f(-1, 1, -1));
		return temp;
	}

	void CCamera::Shutdown()
	{
		Core::Engine::StaticClass()->GetRenderer()->SetCamera(nullptr);
	}
}