#include "Graphics\Bases\BaseRenderer.h"

namespace Graphics
{
	void BaseRenderer::AddRenderable(SEntityDesc &a_Desc)
	{
		if (a_Desc.MeshRenderer == nullptr)
			return;

		if (m_Entities.find(a_Desc.MeshRenderer) != m_Entities.end())
		{
			LogErr("CMeshrenderer is already added\n");
			return;
		}

		std::unique_ptr<IEntity> temp = m_CreateEntity();

		if (!temp->Initialize(a_Desc, this))
		{
			LogErr("Error while trying to add a new Renderable\n");
			return;
		}

		m_Entities.insert({ a_Desc.MeshRenderer, std::move(temp) });
	}

	void BaseRenderer::RemoveRenderable(Scene::CMeshRenderer *a_MeshRenderer)
	{
		if (a_MeshRenderer == nullptr)
			return;

		if (m_Entities.find(a_MeshRenderer) == m_Entities.end())
		{
			LogErr("CMeshrenderer was not found\n");
			return;
		}
		else
		{
			m_Entities.erase(a_MeshRenderer);
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
			RemoveRenderable(desc->MeshRenderer);
			break;

		case Core::EEvents::SCENE_CAMERACOMPONENT_REMOVED:
			m_Camera = nullptr;
			break;
		}
	}
}