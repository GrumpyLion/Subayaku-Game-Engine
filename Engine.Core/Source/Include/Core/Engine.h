#pragma once

#include "SEngineContext.h"
#include "Graphics\Interface\SRendererDesc.h"
#include <GrumpyZip\ZipFile.h>

#define ENGINE_ZIPFILE Core::Engine::StaticClass()->ZipFile
#define ENGINE_CONTEXT Core::Engine::StaticClass()->GetContext()
#define ENGINE_RENDERER Core::Engine::StaticClass()->GetRenderer()

namespace Graphics
{
	class IRenderer;
	class IRenderFactory;
}

namespace Scene
{
	class Scene;
}

namespace Core
{
	class IWindow;
	class InputManager;

	class Engine
	{
	private:
		SEngineContext m_Context{};

		static Engine* m_SharedInstance;
		IWindow* m_Window = nullptr;
		InputManager* m_InputManager = nullptr;

		Scene::Scene* m_Scene = nullptr;

		Graphics::IRenderer* m_Renderer = nullptr;
		Graphics::IRenderFactory* m_RenderFactory = nullptr;

	private:
		//Switches to the currently defined renderer in the render context
		bool SwitchRenderer(SEngineContext &a_Context);

		long m_StartTime = 0;
	public:

		std::unique_ptr<GrumpyZip::ZipFile> ZipFile = nullptr;
		long TimeSinceStart = 0;

		__declspec(dllexport) Engine();
		__declspec(dllexport) ~Engine();

		__declspec(dllexport) bool Initialize(SEngineContext& a_Context);
		__declspec(dllexport) void Run();
		__declspec(dllexport) bool Shutdown();

		Graphics::IRenderer *GetRenderer();
		SEngineContext &GetContext();

		IWindow *GetWindow();
		InputManager *GetInputManager();
		Scene::Scene *GetScene();
		static Engine* StaticClass();

	};
}