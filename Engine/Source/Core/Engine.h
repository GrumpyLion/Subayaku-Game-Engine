#pragma once

#include "SEngineContext.h"
#include "Graphics\Interface\SRendererDesc.h"

namespace Scene
{
	class Scene;
}

namespace Graphics
{
	class IRenderer;
	class TextureCache;
	class IRenderFactory;
}

namespace Core
{
	class IWindow;
	class Keyboard;
	class Cache;

	class Engine
	{
	private:
		SEngineContext m_Context{};

		static Engine* m_SharedInstance;
		IWindow* m_Window = nullptr;
		Keyboard* m_Keyboard = nullptr;
		Cache *m_Cache = nullptr;

		Scene::Scene *m_Scene = nullptr;

		Graphics::IRenderer* m_Renderer = nullptr;
		Graphics::IRenderFactory* m_RenderFactory = nullptr;
		

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
		Keyboard *GetKeyboard();
		Scene::Scene *GetScene();
		SEngineContext &GetContext();
		static Engine* StaticClass();

	};
}