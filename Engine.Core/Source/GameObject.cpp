#include "Scene\GameObject\GameObject.h"

#include "Utilities\Utilities.h"
#include "Scene\GameObject\Components\Transformation.h"
#include "Scene\GameObject\Components\CCamera.h"
#include "Scene\GameObject\Components\CMeshRenderer.h"
#include "Scene\GameObject\Components\CScriptComponent.h"

#include <memory>

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

	void GameObject::SetTransform(Transformation& a_Transform)
	{
		m_Transform = a_Transform;
		Transform = &m_Transform;
	}
	
	bool GameObject::AddComponent(std::unique_ptr<IComponent> a_ToAdd)
	{
		m_Components.push_back(std::move(a_ToAdd));
		return true;
	}

	IComponent* GameObject::AddNewComponent(ComponentType a_Type)
	{
		switch (a_Type)
		{

		case ComponentType::Camera:
			{
				auto temp = std::make_unique<CCamera>();
				auto ptr = temp.get();
				AddComponent(std::move(temp));
				return ptr;
			}

		case ComponentType::MeshRenderer:
			{
				auto temp = std::make_unique<CMeshRenderer>();
				auto ptr = temp.get();
				AddComponent(std::move(temp));
				return ptr;
			}
		case ComponentType::Script:
			{
				auto temp = std::make_unique<CScriptComponent>();
				auto ptr = temp.get();
				AddComponent(std::move(temp));
				return ptr;
			}
		}

		return nullptr;
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