#include "GameObject.h"

#include "Utilities\Utilities.h"
#include "Components\Transformation.h"
#include <memory>
#include "Scene\GameObject\Components\CCamera.h"

namespace Scene
{
	GameObject::~GameObject()
	{
		m_Components.clear();
	}

	bool GameObject::Initialize()
	{
		m_Components.clear();
		return true;
	}

	void GameObject::SetTransform(std::unique_ptr<Transformation> a_Transform)
	{
		m_Transform = std::move(a_Transform);
		Transform = m_Transform.get();
	}
	
	bool GameObject::AddComponent(std::unique_ptr<IComponent> a_ToAdd)
	{
		m_Components.push_back(std::move(a_ToAdd));
		return true;
	}

	void GameObject::RemoveComponentByType(ComponentType &a_Type)
	{
		for (auto &temp : m_Components)
		{
			if (temp->Type == a_Type)
			{
				//TODO
				break;
			}
		}
	}

	void GameObject::Update()
	{
		for (auto &temp : m_Components)
			temp->Update();
	}
}