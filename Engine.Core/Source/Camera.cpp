#include "Include\Graphics\Camera.h"

#include "Core\Engine.h"

namespace Graphics
{
	void Camera::UpdatePerspective(Scene::Transformation &a_Transform, float a_Width, float a_Height)
	{
		Transform = a_Transform;

		float aspect = a_Width / a_Height;

		ToProjectionMatrixRH = Matrix4f::PerspectiveRH(FOV,
			aspect, Near, Far);

		ToProjectionMatrixLH = Matrix4f::PerspectiveLH(FOV,
			aspect, Near, Far);
		

		ToViewMatrixLH = Matrix4f::Identity();
		ToViewMatrixLH *= Matrix4f::RotateX(a_Transform.Rotation.x * DEGTORAD);
		ToViewMatrixLH *= Matrix4f::RotateY(a_Transform.Rotation.y * DEGTORAD);
		ToViewMatrixLH *= Matrix4f::RotateZ(a_Transform.Rotation.z * DEGTORAD);
		ToViewMatrixLH *= Matrix4f::Translate(a_Transform.Position * Vector3f(1, -1, 1));

		ToViewMatrixRH = Matrix4f::Identity();
		ToViewMatrixRH *= Matrix4f::Translate(a_Transform.Position);
		ToViewMatrixRH *= Matrix4f::RotateX(a_Transform.Rotation.x * DEGTORAD);
		ToViewMatrixRH *= Matrix4f::RotateY(a_Transform.Rotation.y * DEGTORAD);
		ToViewMatrixRH *= Matrix4f::RotateZ(a_Transform.Rotation.z * DEGTORAD);
	}

	void Camera::UpdateOrthographic(Scene::Transformation &a_Transform, float a_Left, float a_Right, float a_Top, float a_Bottom)
	{
		Transform = a_Transform;

		ToProjectionMatrixLH = Matrix4f::Orthograpic(a_Left, a_Right, a_Top, a_Bottom, Near, Far);

		ToViewMatrixLH = Matrix4f::Identity();
		ToViewMatrixLH *= Matrix4f::RotateX(a_Transform.Rotation.x * DEGTORAD);
		ToViewMatrixLH *= Matrix4f::RotateY(a_Transform.Rotation.y * DEGTORAD);
		ToViewMatrixLH *= Matrix4f::RotateZ(a_Transform.Rotation.z * DEGTORAD);
		ToViewMatrixLH *= Matrix4f::Translate(a_Transform.Position * Vector3f(1, -1, 1));

		ToViewMatrixRH = Matrix4f::Identity();
		ToViewMatrixRH *= Matrix4f::Translate(a_Transform.Position);
		ToViewMatrixRH *= Matrix4f::RotateX(a_Transform.Rotation.x * DEGTORAD);
		ToViewMatrixRH *= Matrix4f::RotateY(a_Transform.Rotation.y * DEGTORAD);
		ToViewMatrixRH *= Matrix4f::RotateZ(a_Transform.Rotation.z * DEGTORAD);
	}
}