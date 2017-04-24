#pragma once

namespace Scene
{
	enum ComponentType
	{
		Transform,
		MeshRenderer,
		Camera,
		Script,
		Sprite
	};

	class GameObject;

	class IComponent
	{
	public:
		ComponentType Type;
		GameObject *Parent = nullptr;

		virtual ~IComponent() {}

		//Called once for initialization
		virtual bool Initialize(GameObject *a_Parent)
		{
			Parent = a_Parent;	
			return true;
		}
		//Called 60 times a second
		virtual void Update() = 0;
		//Called if the GameObject or this particular component gets destroyed
		virtual void Shutdown() = 0;
	};
}