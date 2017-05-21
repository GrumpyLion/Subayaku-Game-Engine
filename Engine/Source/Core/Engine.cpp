#include "Engine.h"
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

		m_Window = std::make_unique<Window>();

		if (!m_Window->Initialize(a_Context))
		{
			ErrorBox(L"Window Init Failure");
			return false;
		}

		m_ZipFile = std::make_unique<GrumpyZip::ZipFile>();

		if (!m_ZipFile->LoadZipFile(a_Context.PathToPak))
			return false;		

		if (!SwitchRenderer(a_Context))
			return false;

		m_InputManager = std::make_unique<InputManager>();

		m_InputManager->Initialize();

		m_Scene = std::make_unique<Scene::Scene>();

		if (!m_Scene->Initialize())
		{
			ErrorBox(L"Scene Init Failure");
			return false;
		}
		
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
		int index = 0;

		while (!done)
		{

			//We need to check for messages if we get an Quit message we end the loop
			if (!m_Window->Update())
				done = true;

			auto delta = clock::now() - start;
			start = clock::now();
			lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta);

			while (lag >= timestep)
			{
				GetInputManager()->GetKeyboard()->Update();
				lag -= timestep;
				updates++;
				if (GetInputManager()->GetKeyboard()->IsKeyJustDown(SUBA_KEY_ESCAPE))
				{
					done = true;
				}

				GetInputManager()->Update();
				
				m_Scene->Update();
			
				//Remove later..
				if (GetInputManager()->GetKeyboard()->IsKeyJustDown(SUBA_KEY_O))
				{
					m_Context.RDevice = RenderDevice::DirectX;
					SwitchRenderer(m_Context);
				}

				if (GetInputManager()->GetKeyboard()->IsKeyJustDown(SUBA_KEY_P))
				{
					m_Context.RDevice = RenderDevice::OpenGL;
					SwitchRenderer(m_Context);
				}

				GetInputManager()->GetKeyboard()->Refresh();
			}

			auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - deltaTimer);
			deltaTimer = std::chrono::high_resolution_clock::now();

			long nowTimer = (long)std::chrono::duration_cast<std::chrono::milliseconds>
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
			Sleep(1);
		}
	}

	bool Engine::Shutdown()
	{
		m_InputManager.reset();

		m_Scene->ClearScene();
		m_Scene.reset();

		m_Renderer.reset();

		m_Window.reset();

		m_Cache.reset();

		m_ZipFile.reset();
		return true;
	}
	
	bool Engine::SwitchRenderer(SEngineContext &a_Context)
	{
		//Shutdown the old renderer
		m_Renderer.reset();
		m_Cache.reset();

		m_Cache = std::make_unique<Cache>();

		switch (a_Context.RDevice)
		{
		case RenderDevice::OpenGL:
			m_Renderer = std::make_unique<Graphics::OpenGL::GLRenderer>();
			m_Cache->Initialize(std::make_unique<Graphics::OpenGL::GLRenderFactory>(), m_ZipFile.get());
			break;

		case RenderDevice::DirectX:
			m_Renderer = std::make_unique<Graphics::DirectX::D3DRenderer>();
			m_Cache->Initialize(std::make_unique<Graphics::DirectX::D3DRenderFactory>(), m_ZipFile.get());
			break;
		
		default:
			ErrorBox(L"Unknown Renderer");
			return false;
		}

		Graphics::SRendererDesc rendererDesc{};
		rendererDesc.Handle = static_cast<Window*>(GetWindow())->GetHandle();
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
	{	return m_Cache.get();		}

	IWindow *Engine::GetWindow()
	{	return m_Window.get();	}

	Graphics::IRenderer *Engine::GetRenderer()
	{	return m_Renderer.get();	}

	InputManager *Engine::GetInputManager()
	{	return m_InputManager.get();	}

	Scene::Scene *Engine::GetScene()
	{	return m_Scene.get();		}

	SEngineContext &Engine::GetContext()
	{	return m_Context;	}

	Engine* Engine::StaticClass()
	{	return m_SharedInstance;	}

}