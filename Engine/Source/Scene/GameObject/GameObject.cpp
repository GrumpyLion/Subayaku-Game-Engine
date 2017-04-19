#include "GameObject.h"

#include "Utilities\Utilities.h"

namespace Scene
{
	GameObject::~GameObject()
	{	Shutdown();	}

	bool GameObject::Initialize()
	{
		m_Components.clear();

		return true;
	}

	bool GameObject::AddComponent(IComponent *a_ToAdd)
	{
		if (a_ToAdd == nullptr)	
			return false;

		a_ToAdd->Initialize(this);
		m_Components.push_back(a_ToAdd);
		return true;
	}

	void GameObject::RemoveAllComponents()
	{
		for (auto &temp : m_Components)
			SHUTDOWN_AND_DELETE(temp);
		m_Components.clear();
	}

	void GameObject::RemoveComponentByType(ComponentType &a_Type)
	{
		for (auto &temp : m_Components)
		{
			if (temp->Type == a_Type)
			{
				SHUTDOWN_AND_DELETE(temp);
				break;
			}
		}
	}

	void GameObject::Update()
	{
		for (auto &temp : m_Components)
			temp->Update();
	}

	void GameObject::Shutdown()
	{
		SAFE_DELETE(Transform);
		RemoveAllComponents();
	}
}