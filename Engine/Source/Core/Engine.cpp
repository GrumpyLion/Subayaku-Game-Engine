#include "SubayakuCore.h"
#include <chrono>

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

		//For keeping the updates to the desired amount in one second
		auto lastTime = std::chrono::high_resolution_clock::now();
		auto deltaTimer = std::chrono::high_resolution_clock::now();
		long lastTimer = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

		double delta = 0;
		double nsPerTick = 1000000000 / 60;

		int frames = 0;
		int updates = 0;

		while (!done)
		{
			//We need to check for messages if we get an Quit message we end the loop
			if (!m_Window->Update())
				done = true;

			auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - deltaTimer);
			deltaTimer = std::chrono::high_resolution_clock::now();

			//Time calculations
			auto now = std::chrono::high_resolution_clock::now();
			delta += std::chrono::duration_cast<std::chrono::nanoseconds>(now - lastTime).count() / nsPerTick;
			lastTime = std::chrono::high_resolution_clock::now();

			while (delta >= 1)
			{
				if (delta > 2) delta = 0;

				updates++;
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

				m_Scene->Update();
				delta -= 1;
			}

			long nowTimer = std::chrono::duration_cast<std::chrono::milliseconds>
				(std::chrono::system_clock::now().time_since_epoch()).count();
			if (nowTimer - lastTimer >= 1000)
			{
				printf("Frames %i, Ticks %i\n", frames, updates);
				updates = 0;
				frames = 0;
				lastTimer += 1000;
			}

			m_Renderer->Render();
			frames++;
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