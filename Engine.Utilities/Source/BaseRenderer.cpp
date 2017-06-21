#include "Graphics\Bases\BaseRenderer.h"

namespace Graphics
{
	void BaseRenderer::AddRenderable(SEntityDesc &a_Desc)
	{
		if (a_Desc.MeshRenderer == nullptr)
			return;

		//Entity is already added with this materials
		if (m_Entities.find(a_Desc) != m_Entities.end())
		{
			m_Entities.find(a_Desc)->second->AddInstance(a_Desc.MeshRenderer);
			return;
		}
		//nothing found
		std::unique_ptr<IEntity> temp = m_CreateEntity();

		if (!temp->Initialize(a_Desc, this))
		{
			LogErr("Error while trying to add a new Renderable");
			return;
		}

		m_Entities.insert({ a_Desc, std::move(temp) });
	}

	void BaseRenderer::RemoveRenderable(SEntityDesc &a_Desc)
	{
		if (a_Desc.MeshRenderer == nullptr)
			return;

		if (m_Entities.find(a_Desc) == m_Entities.end())
		{
			LogErr("Entity was not found");
			return;
		}
		else
		{
			auto temp = m_Entities.find(a_Desc);

			if (temp->second->GetInstanceCount() > 1)
			{
				temp->second->RemoveInstance(a_Desc.MeshRenderer);
			}
			else
			{
				m_Entities.erase(a_Desc);
			}
		}
	}

	void BaseRenderer::EventListener(Core::SEventDesc &a_Desc)
	{
		SEntityDesc *desc = static_cast<SEntityDesc*>(a_Desc.Description);
		
		switch (a_Desc.Event)
		{
		case Core::EEvents::SCENE_MESHCOMPONENT_ADDED:
			AddRenderable(*desc);
			break;

		case Core::EEvents::SCENE_CAMERACOMPONENT_ADDED:
			m_Camera = (Scene::CCamera*)a_Desc.Description;
			break;

		case Core::EEvents::SCENE_MESHCOMPONENT_REMOVED:
			RemoveRenderable(*desc);
			break;

		case Core::EEvents::SCENE_CAMERACOMPONENT_REMOVED:
			m_Camera = nullptr;
			break;

		case Core::EEvents::SCENE_CLEAR:
			m_Entities.clear();
			break;
		}
	}
}