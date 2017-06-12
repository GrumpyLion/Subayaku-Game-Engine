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

	bool CCamera::Initialize(GameObject *a_Parent, float a_FOV, float a_Near, float a_Far)
	{
		IComponent::Initialize(a_Parent);

		FOV = a_FOV;
		Near = a_Near;
		Far = a_Far;

		CurrentCamera = true;

		Core::SEventDesc eventDesc{};

		eventDesc.Event = Core::EEvents::SCENE_CAMERACOMPONENT_ADDED;
		eventDesc.Description = this;

		Core::EventHandler::StaticClass()->AddEvent(eventDesc);

		return true;
	}

	void CCamera::Update()
	{
		float aspect = (float)Core::Engine::StaticClass()->GetContext().Width / (float)Core::Engine::StaticClass()->GetContext().Height;
		ToProjectionMatrixRH = Matrix4f::PerspectiveRH(FOV,
			aspect, Near, Far);

		ToProjectionMatrixLH = Matrix4f::PerspectiveLH(FOV,
			aspect, Near, Far);

		ToViewMatrixLH = Matrix4f::Identity();
		ToViewMatrixLH *= Matrix4f::RotateX(Parent->Transform->Rotation.x * DEGTORAD);
		ToViewMatrixLH *= Matrix4f::RotateY(Parent->Transform->Rotation.y * DEGTORAD);
		ToViewMatrixLH *= Matrix4f::RotateZ(Parent->Transform->Rotation.z * DEGTORAD);
		ToViewMatrixLH *= Matrix4f::Translate(Parent->Transform->Position * Vector3f(1, -1, 1));

		ToViewMatrixRH = Matrix4f::Identity();
		ToViewMatrixRH *= Matrix4f::Translate(Parent->Transform->Position);
		ToViewMatrixRH *= Matrix4f::RotateX(Parent->Transform->Rotation.x * DEGTORAD);
		ToViewMatrixRH *= Matrix4f::RotateY(Parent->Transform->Rotation.y * DEGTORAD);
		ToViewMatrixRH *= Matrix4f::RotateZ(Parent->Transform->Rotation.z * DEGTORAD);
	}
}