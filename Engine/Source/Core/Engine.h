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
}

namespace Core
{
	class IWindow;
	class Keyboard;

	class Engine
	{
	private:
		SEngineContext m_Context{};

		static Engine* m_SharedInstance;
		IWindow* m_Window = nullptr;
		Graphics::IRenderer* m_Renderer = nullptr;
		Keyboard* m_Keyboard = nullptr;
		Scene::Scene *m_Scene = nullptr;

		//Caches
		Graphics::TextureCache *m_TextureCache = nullptr;

	private:
		bool SwitchRenderer(SEngineContext &a_Context);

	public:
		Engine();
		~Engine();

		bool Initialize(SEngineContext& a_Context);
		void Run();
		bool Shutdown();

		IWindow *GetWindow();
		Graphics::IRenderer *GetRenderer();
		Keyboard *GetKeyboard();
		Scene::Scene *GetScene();
		Graphics::TextureCache *GetTextureCache();

		static Engine* StaticClass();
	};
}