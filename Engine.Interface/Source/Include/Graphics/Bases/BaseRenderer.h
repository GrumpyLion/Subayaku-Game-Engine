#pragma once

#include "Graphics\Interfaces\IRenderer.h"
#include "Graphics\Utilities\GraphicsCache.h"

#include "Graphics\Interfaces\IEntity.h"

namespace Graphics
{
	class BaseRenderer : public IRenderer
	{
	protected:
		Core::Engine *m_Engine = nullptr;
		Scene::CCamera *m_Camera = nullptr;

		//Container for all entities
		//
		std::unordered_map<Scene::CMeshRenderer*, std::unique_ptr<IEntity>> m_Entities;

		//This will cache all objects so we only need to create and load them once. Will be destroyed if the renderer changes..
		//
		std::unique_ptr<GraphicsCache> m_Cache;

		//Lambda to create all entities
		//
		std::function<std::unique_ptr<IEntity>()> m_CreateEntity;

	public:
		virtual ~BaseRenderer() 
		{		}

		BaseRenderer(Core::Engine *a_Engine)
			: m_Engine(a_Engine), m_Cache(std::make_unique<GraphicsCache>(this))
		{		}

		Core::Engine *GetEngine()	final				{			return m_Engine;			}

		GraphicsCache* GetCache()						{			return m_Cache.get();		}

		Scene::CCamera* GetCamera()	final				{			return m_Camera;			}
		
		void SetCamera(Scene::CCamera *a_Camera) final	{			m_Camera = a_Camera;		}

		//Adds an renderer entity object that contains all information to render an certain object.
		//
		void AddRenderable(SEntityDesc &a_Desc, Scene::CMeshRenderer *a_MeshRenderer) final;

		//Removes an entity with the given meshrenderer
		//
		void RemoveRenderable(Scene::CMeshRenderer *a_MeshRenderer) final;
	};
}