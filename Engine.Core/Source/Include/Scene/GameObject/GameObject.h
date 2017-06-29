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
		Transformation m_Transform;

	public:
		//This represents the position, rotation and the scale
		Transformation* Transform = nullptr;
		std::unique_ptr<Matrix4f> ModelTransform;
		bool IsTicking = true;
		std::string Name = "Unnamed";

		~GameObject();
		
		void SetTransform(Transformation& a_Transform);
		bool Initialize();
		void Update();

		bool AddComponent(std::unique_ptr<IComponent> a_ToAdd);
		IComponent* AddNewComponent(ComponentType a_Type);
		void RemoveComponentByType(ComponentType &a_Type);
	};
}