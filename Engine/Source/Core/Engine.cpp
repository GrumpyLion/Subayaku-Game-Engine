#include "SubayakuCore.h"

namespace Core
{
	Engine* Engine::m_SharedInstance = nullptr;

	Engine::Engine()
	{
		m_SharedInstance = this;
	}

	Engine::~Engine()
	{
		Shutdown();
	}
	
	bool Engine::Initialize(SEngineContext& a_Context)
	{		
		m_Context = a_Context;

		m_Window = new CWindow();

		if (!m_Window->Initialize(a_Context))
		{
			ErrorBox(L"Window Init Failure");
			return false;
		}

		if (!SwitchRenderer(a_Context))
			return false;

		m_Scene = new Scene::Scene();

		if (!m_Scene->Initialize())
		{
			ErrorBox(L"Scene Init Failure");
			return false;
		}

		m_Keyboard = new Keyboard();

		m_Keyboard->Init();

		return true;
	}

	void Engine::Run()
	{
		bool done = false;

		while (!done)
		{
			//We need to check for messages if we get an Quit message we end the loop
			if (!m_Window->Update())
				done = true;

			m_Scene->Update();

			m_Renderer->Render();

			if (GetKeyboard()->IsKeyDown(SUBA_KEY_E))
			{
				m_Context.RDevice = RenderDevice::DirectX;
				SwitchRenderer(m_Context);
			}

			if (GetKeyboard()->IsKeyDown(SUBA_KEY_R))
			{
				m_Context.RDevice = RenderDevice::OpenGL;
				SwitchRenderer(m_Context);
			}

			if (GetKeyboard()->IsKeyDown(SUBA_KEY_ESCAPE))
			{
				done = true;
			}
		}

		Shutdown();
	}

	bool Engine::Shutdown()
	{
		SAFE_DELETE(m_Keyboard);

		SHUTDOWN_AND_DELETE(m_Scene);
	
		SHUTDOWN_AND_DELETE(m_Renderer);
		
		SHUTDOWN_AND_DELETE(m_Window);
		return true;
	}
	
	bool Engine::SwitchRenderer(SEngineContext &a_Context)
	{
		//Shutdown the old renderer
		SHUTDOWN_AND_DELETE(m_Renderer);

		switch (a_Context.RDevice)
		{
		case RenderDevice::OpenGL:
			m_Renderer = new Graphics::OpenGL::GLRenderer();
			break;

		case RenderDevice::DirectX:
			m_Renderer = new Graphics::DirectX::D3DRenderer();	
			break;
		
		default:
			ErrorBox(L"Unknown Renderer");
			return false;
		}

		Graphics::SRendererDesc rendererDesc{};
		rendererDesc.Handle = static_cast<CWindow*>(m_Window)->GetHandle();
		rendererDesc.Width = a_Context.Width;
		rendererDesc.Height = a_Context.Height;

		if (!m_Renderer->Initialize(rendererDesc))
		{
			ErrorBox(L"Renderer Init Failure");
			return false;
		}

		return true;
	}

	IWindow *Engine::GetWindow()
	{	return m_Window;	}

	Graphics::IRenderer *Engine::GetRenderer()
	{	return m_Renderer;	}

	Keyboard *Engine::GetKeyboard()
	{	return m_Keyboard;	}

	Scene::Scene *Engine::GetScene()
	{	return m_Scene;	}

	Engine* Engine::StaticClass()
	{	return m_SharedInstance;	}

}