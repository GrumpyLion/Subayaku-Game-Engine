#pragma once

namespace Scene
{
	enum ComponentType
	{
		Transform,
		MeshRenderer,
		Camera,
		Script,
		Sprite,
		Light,
		Rigidbody,
		BoxCollider,
		SphereCollider,
		MeshCollider,
		CapsuleCollider
	};

	class GameObject;

	class IComponent
	{
	public:
		ComponentType Type;
		GameObject *Parent = nullptr;

		virtual ~IComponent() {}

		//Called once for initialization
		IComponent(GameObject *a_Parent)
			: Parent(a_Parent) { }
		
		//Called 60 times a second
		virtual void Update() = 0;
	};
}