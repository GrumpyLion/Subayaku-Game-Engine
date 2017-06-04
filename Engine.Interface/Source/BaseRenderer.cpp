#include "Graphics\Bases\BaseRenderer.h"

namespace Graphics
{
	void BaseRenderer::AddRenderable(SEntityDesc &a_Desc, Scene::CMeshRenderer *a_MeshRenderer)
	{
		if (a_MeshRenderer == nullptr)
			return;

		if (m_Entities.find(a_MeshRenderer) != m_Entities.end())
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

		m_Entities.insert({ a_MeshRenderer, std::move(temp) });
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
}