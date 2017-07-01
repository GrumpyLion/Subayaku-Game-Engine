#pragma once

#include "Graphics\Interfaces\IRenderer.h"
#include "Graphics\Utilities\GraphicsCache.h"

#include "Graphics\Interfaces\IEntity.h"

#include "Scene\GameObject\Components\CLight.h"

namespace Graphics
{
	class BaseRenderer : public IRenderer
	{
	protected:
		Core::Engine *m_Engine = nullptr;
		Scene::CCamera *m_Camera = nullptr;

		// Container for all entities
		//
		std::unordered_map<SEntityDesc, std::unique_ptr<IEntity>> m_Entities;

		// This will cache all objects so we only need to create and load them once. Will be destroyed if the renderer changes..
		//
		std::unique_ptr<GraphicsCache> m_Cache;

		// Lambda to create all entities
		//
		std::function<std::unique_ptr<IEntity>()> m_CreateEntity = nullptr;

		// Function* to EventHandler
		//
		std::function<void(Core::SEventDesc&)> m_EventListener = nullptr;

		// Directional Light. Only one can exist in one scene at this time
		//
		Scene::CLight *m_DirectionalLight = nullptr;
		
		// Renderer Settings here
		//
		SRendererDesc m_Desc{};

		// Will be called at WINDOW_RESIZE EVENT
		// Resize G-Buffer & so on
		virtual void Resize() = 0;

	public:
		virtual ~BaseRenderer() 
		{
			Core::EventHandler::StaticClass()->Unsubscribe(m_EventListener, Core::EEvents::SCENE_MESHCOMPONENT_ADDED);
			Core::EventHandler::StaticClass()->Unsubscribe(m_EventListener, Core::EEvents::SCENE_CAMERACOMPONENT_ADDED);

			Core::EventHandler::StaticClass()->Unsubscribe(m_EventListener, Core::EEvents::SCENE_MESHCOMPONENT_REMOVED);
			Core::EventHandler::StaticClass()->Unsubscribe(m_EventListener, Core::EEvents::SCENE_CAMERACOMPONENT_REMOVED);

			Core::EventHandler::StaticClass()->Unsubscribe(m_EventListener, Core::EEvents::SCENE_LIGHT_ADDED);
			Core::EventHandler::StaticClass()->Unsubscribe(m_EventListener, Core::EEvents::SCENE_LIGHT_REMOVED);

			Core::EventHandler::StaticClass()->Unsubscribe(m_EventListener, Core::EEvents::WINDOW_RESIZE);
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

			Core::EventHandler::StaticClass()->Subscribe(m_EventListener, Core::EEvents::WINDOW_RESIZE);

			Core::EventHandler::StaticClass()->Subscribe(m_EventListener, Core::EEvents::SCENE_LIGHT_ADDED);
			Core::EventHandler::StaticClass()->Subscribe(m_EventListener, Core::EEvents::SCENE_LIGHT_REMOVED);
		}

		Core::Engine *GetEngine()	final				{			return m_Engine;			}

		GraphicsCache *GetCache()						{			return m_Cache.get();		}

		Scene::CCamera *GetCamera()	final				{			return m_Camera;			}

		Scene::CLight *GetDirectionalLight()			{			return m_DirectionalLight;	}

		//Adds an renderer entity object that contains all information to render a certain object.
		//
		__declspec(dllexport) void AddRenderable(SEntityDesc &a_Desc) final;

		//Removes an entity with the given meshrenderer
		//
		__declspec(dllexport) void RemoveRenderable(SEntityDesc &a_Desc) final;

		__declspec(dllexport) void EventListener(Core::SEventDesc &a_Desc) final;
	};
}