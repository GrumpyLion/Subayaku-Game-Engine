#pragma once

#include "Components\Interface\IComponent.h"

#include <vector>
#include <string>

namespace Scene
{
	class IComponent;
	class Transformation;

	class GameObject
	{
	private:
		std::vector<IComponent*> m_Components{};

	public:
		//This represents the position, rotation and the scale
		Transformation *Transform = nullptr;
		std::string Name = "Unnamed";

		~GameObject();
		
		bool Initialize();
		void Update();
		void Shutdown();

		bool AddComponent(IComponent *a_ToAdd);
		void RemoveAllComponents();
		void RemoveComponentByType(ComponentType &a_Type);
	};
}