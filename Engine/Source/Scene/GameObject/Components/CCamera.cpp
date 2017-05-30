#include "CCamera.h"
#include "Core\Engine.h"
#include "Scene\Scene.h"

#include "Graphics\Interface\IRenderer.h"
#include "Input\InputManager.h"

namespace Scene
{
	CCamera::~CCamera()
	{
		Core::Engine::StaticClass()->GetRenderer()->SetCamera(nullptr);
	}

	bool CCamera::Initialize(GameObject *a_Parent, float a_FOV, float a_Near, float a_Far)
	{
		IComponent::Initialize(a_Parent);

		FOV = a_FOV;
		Near = a_Near;
		Far = a_Far;

		CurrentCamera = true;
		return true;
	}

	void CCamera::Update()
	{
		Core::Engine::StaticClass()->GetRenderer()->SetCamera(this);
		Core::Engine::StaticClass()->GetScene()->SetCamera(this);

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
		temp *= Matrix4f::RotateX(Parent->Transform->Rotation.x * DEGTORAD);
		temp *= Matrix4f::RotateY(Parent->Transform->Rotation.y * DEGTORAD);
		temp *= Matrix4f::RotateZ(Parent->Transform->Rotation.z * DEGTORAD);
		temp *= Matrix4f::Translate(Parent->Transform->Position);
		return temp;
	}
}