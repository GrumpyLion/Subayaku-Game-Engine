#pragma once

#include "Components\Interface\IComponent.h"
#include "Components\Transformation.h"

#include <vector>
#include <string>
#include <memory>

namespace Scene
{
	class GameObject
	{
	private:
		std::vector<std::unique_ptr<IComponent>> m_Components;
		std::unique_ptr<Transformation> m_Transform;

	public:
		//This represents the position, rotation and the scale
		Transformation* Transform = nullptr;
		std::string Name = "Unnamed";

		~GameObject();
		
		void SetTransform(std::unique_ptr<Transformation> a_Transform);
		bool Initialize();
		void Update();

		bool AddComponent(std::unique_ptr<IComponent> a_ToAdd);
		void RemoveComponentByType(ComponentType &a_Type);
	};
}