#pragma once

#include "SEngineContext.h"
#include "Graphics\Descriptions\SRendererDesc.h"

#include "Utilities\Event\EventHandler.h"

#define ENGINE_CONTEXT Core::Engine::StaticClass()->GetContext()
#define ENGINE_RENDERER Core::Engine::StaticClass()->GetRenderer()

namespace Graphics
{
	class IRenderer;
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
		static Engine* m_SharedInstance;
		IWindow* m_Window = nullptr;
		InputManager* m_InputManager = nullptr;

		Scene::Scene* m_Scene = nullptr;

		Graphics::IRenderer* m_Renderer = nullptr;

	private:
		//Switches to the currently defined renderer in the render context
		bool SwitchRenderer(SEngineContext &a_Context);
		bool LoadSceneFromDLL();

		long m_StartTime = 0;
	public:
		SEngineContext m_Context{};
		long TimeSinceStart = 0;

		__declspec(dllexport) Engine();
		__declspec(dllexport) ~Engine();

		__declspec(dllexport) bool Initialize(SEngineContext& a_Context);
		__declspec(dllexport) void Run();
		__declspec(dllexport) bool Shutdown();

		Graphics::IRenderer *GetRenderer()	{	return m_Renderer;		 };
		SEngineContext &GetContext()		{	return m_Context;		 };
		IWindow *GetWindow()				{	return m_Window;		 };
		InputManager *GetInputManager()		{	return m_InputManager;	 };
		Scene::Scene *GetScene()			{	return m_Scene;			 };
		static Engine* StaticClass()		{	return m_SharedInstance; };

	};
}