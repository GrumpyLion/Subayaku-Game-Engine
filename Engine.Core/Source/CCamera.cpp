#include "Scene\GameObject\Components\CCamera.h"
#include "Core\Engine.h"
#include "Scene\Scene.h"

#include "Graphics\Interfaces\IRenderer.h"
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

		float aspect = (float)Core::Engine::StaticClass()->GetContext().Width / (float)Core::Engine::StaticClass()->GetContext().Height;
		ToProjectionMatrixRH = Matrix4f::PerspectiveRH(FOV,
			aspect, Near, Far);

		ToProjectionMatrixLH = Matrix4f::PerspectiveLH(FOV,
			aspect, Near, Far);

		ToViewMatrixLH = Matrix4f::Identity();
		ToViewMatrixLH *= Matrix4f::RotateX(Parent->Transform->Rotation.x * DEGTORAD);
		ToViewMatrixLH *= Matrix4f::RotateY(Parent->Transform->Rotation.y * DEGTORAD);
		ToViewMatrixLH *= Matrix4f::RotateZ(Parent->Transform->Rotation.z * DEGTORAD);
		ToViewMatrixLH *= Matrix4f::Translate(Parent->Transform->Position);

		ToViewMatrixRH = Matrix4f::Identity();
		ToViewMatrixRH *= Matrix4f::Translate(Parent->Transform->Position);
		ToViewMatrixRH *= Matrix4f::RotateX(Parent->Transform->Rotation.x * DEGTORAD);
		ToViewMatrixRH *= Matrix4f::RotateY(Parent->Transform->Rotation.y * DEGTORAD);
		ToViewMatrixRH *= Matrix4f::RotateZ(Parent->Transform->Rotation.z * DEGTORAD);
	}
}