#pragma once

#include "SEngineContext.h"
#include "Graphics\Interface\SRendererDesc.h"
#include "SubayakuCore.h"

#include <memory>

namespace Core
{
	class Engine
	{
	private:
		SEngineContext m_Context{};

		static Engine* m_SharedInstance;
		std::unique_ptr<IWindow> m_Window = nullptr;
		std::unique_ptr<InputManager> m_InputManager = nullptr;
		std::unique_ptr<Cache> m_Cache = nullptr;

		std::unique_ptr<Scene::Scene> m_Scene = nullptr;

		std::unique_ptr<Graphics::IRenderer> m_Renderer = nullptr;
		std::unique_ptr<Graphics::IRenderFactory> m_RenderFactory = nullptr;
		

		//Graphics::TextureCache *m_TextureCache = nullptr;
	private:
		//Switches to the currently defined renderer in the render context
		bool SwitchRenderer(SEngineContext &a_Context);

		long m_StartTime = 0;
	public:
		Engine();
		~Engine();

		bool Initialize(SEngineContext& a_Context);
		void Run();
		bool Shutdown();

		//Returns the time since the start of the game in milliseconds
		long GetTimeSinceStart();
		
		Cache *GetCache();
		IWindow *GetWindow();
		Graphics::IRenderer *GetRenderer();
		InputManager *GetInputManager();
		Scene::Scene *GetScene();
		SEngineContext &GetContext();
		static Engine* StaticClass();

	};
}