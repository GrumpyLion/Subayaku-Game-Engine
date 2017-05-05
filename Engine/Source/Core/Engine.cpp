#include "Engine.h"
#include "SubayakuCore.h"
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

// we use a fixed timestep of 1 / (60 fps) = 16 milliseconds
constexpr std::chrono::nanoseconds timestep(16ms);

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

		//m_TextureCache = new Graphics::TextureCache();

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

		m_InputManager = new InputManager();

		m_InputManager->Initialize();
		
		return true;
	}

	void Engine::Run()
	{
		bool done = false;
		using clock = std::chrono::high_resolution_clock;
		std::chrono::nanoseconds lag(0ns);

		//For keeping the updates to the desired amount in one second
		auto lastTime = std::chrono::high_resolution_clock::now();
		auto deltaTimer = std::chrono::high_resolution_clock::now();
		long lastTimer = (long)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

		m_StartTime = (long)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

		auto start = clock::now();

		int frames = 0;
		int updates = 0;

		while (!done)
		{
			//We need to check for messages if we get an Quit message we end the loop
			if (!m_Window->Update())
				done = true;

			GetInputManager()->Update();

			auto delta = clock::now() - start;
			start = clock::now();
			lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta);

			while (lag >= timestep)
			{
				lag -= timestep;
				updates++;
				if (GetInputManager()->GetKeyboard()->IsKeyDown(SUBA_KEY_ESCAPE))
				{
					done = true;
				}
				
				m_Scene->Update();
			}

			if (GetInputManager()->GetKeyboard()->IsKeyDown(SUBA_KEY_E))
			{
				m_Context.RDevice = RenderDevice::DirectX;
				SwitchRenderer(m_Context);
			}

			if (GetInputManager()->GetKeyboard()->IsKeyDown(SUBA_KEY_R))
			{
				m_Context.RDevice = RenderDevice::OpenGL;
				SwitchRenderer(m_Context);
			}

			auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - deltaTimer);
			deltaTimer = std::chrono::high_resolution_clock::now();

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
			Sleep(2);
		}

		Shutdown();
	}

	bool Engine::Shutdown()
	{
		SAFE_DELETE(m_InputManager);

		SHUTDOWN_AND_DELETE(m_Scene);
	
		SHUTDOWN_AND_DELETE(m_Renderer);
		
		SHUTDOWN_AND_DELETE(m_Window);

		SHUTDOWN_AND_DELETE(m_Cache);

		return true;
	}
	
	bool Engine::SwitchRenderer(SEngineContext &a_Context)
	{
		//Shutdown the old renderer
		SHUTDOWN_AND_DELETE(m_Renderer);
		//Shutdown Cache because cache is renderer relevant
		SHUTDOWN_AND_DELETE(m_Cache);

		m_Cache = new Cache();

		switch (a_Context.RDevice)
		{
		case RenderDevice::OpenGL:
			m_Renderer = new Graphics::OpenGL::GLRenderer();
			m_Cache->Initialize(new Graphics::OpenGL::GLRenderFactory());
			break;

		case RenderDevice::DirectX:
			m_Renderer = new Graphics::DirectX::D3DRenderer();
			m_Cache->Initialize(new Graphics::DirectX::D3DRenderFactory());
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


	long Engine::GetTimeSinceStart()
	{
		return (long)(std::chrono::duration_cast<std::chrono::milliseconds>
			(std::chrono::system_clock::now().time_since_epoch()).count() - m_StartTime);
	}

	Cache *Engine::GetCache()
	{	return m_Cache;		}

	IWindow *Engine::GetWindow()
	{	return m_Window;	}

	Graphics::IRenderer *Engine::GetRenderer()
	{	return m_Renderer;	}

	InputManager *Engine::GetInputManager()
	{	return m_InputManager;	}

	Scene::Scene *Engine::GetScene()
	{	return m_Scene;		}

	SEngineContext &Engine::GetContext()
	{	return m_Context;	}

	Engine* Engine::StaticClass()
	{	return m_SharedInstance;	}

}