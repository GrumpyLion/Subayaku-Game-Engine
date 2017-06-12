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
		std::function<std::unique_ptr<IEntity>()> m_CreateEntity = nullptr;

		//Function* to EventHandler
		//
		std::function<void(Core::SEventDesc&)> m_EventListener = nullptr;

	public:
		virtual ~BaseRenderer() 
		{
			Core::EventHandler::StaticClass()->Unsubscribe(m_EventListener, Core::EEvents::SCENE_MESHCOMPONENT_ADDED);
			Core::EventHandler::StaticClass()->Unsubscribe(m_EventListener, Core::EEvents::SCENE_CAMERACOMPONENT_ADDED);

			Core::EventHandler::StaticClass()->Unsubscribe(m_EventListener, Core::EEvents::SCENE_MESHCOMPONENT_REMOVED);
			Core::EventHandler::StaticClass()->Unsubscribe(m_EventListener, Core::EEvents::SCENE_CAMERACOMPONENT_REMOVED);
		
			Core::EventHandler::StaticClass()->Unsubscribe(m_EventListener, Core::EEvents::SCENE_CLEAR);
		}

		BaseRenderer(Core::Engine *a_Engine)
			: m_Engine(a_Engine), m_Cache(std::make_unique<GraphicsCache>(this))
		{
			m_EventListener = [=](Core::SEventDesc& desc)
			{
				this->EventListener(desc);
			};

			Core::EventHandler::StaticClass()->Subscribe(m_EventListener, Core::EEvents::SCENE_MESHCOMPONENT_ADDED);
			Core::EventHandler::StaticClass()->Subscribe(m_EventListener, Core::EEvents::SCENE_CAMERACOMPONENT_ADDED);	

			Core::EventHandler::StaticClass()->Subscribe(m_EventListener, Core::EEvents::SCENE_MESHCOMPONENT_REMOVED);
			Core::EventHandler::StaticClass()->Subscribe(m_EventListener, Core::EEvents::SCENE_CAMERACOMPONENT_REMOVED);

			Core::EventHandler::StaticClass()->Subscribe(m_EventListener, Core::EEvents::SCENE_CLEAR);
		}

		Core::Engine *GetEngine()	final				{			return m_Engine;			}

		GraphicsCache* GetCache()						{			return m_Cache.get();		}

		Scene::CCamera* GetCamera()	final				{			return m_Camera;			}

		//Adds an renderer entity object that contains all information to render an certain object.
		//
		__declspec(dllexport) void AddRenderable(SEntityDesc &a_Desc) final;

		//Removes an entity with the given meshrenderer
		//
		__declspec(dllexport) void RemoveRenderable(Scene::CMeshRenderer *a_MeshRenderer) final;

		__declspec(dllexport) void EventListener(Core::SEventDesc &a_Desc) final;
	};
}