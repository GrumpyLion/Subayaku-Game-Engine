#include "Core\Engine.h"
#include <chrono>
#include <thread>

#include "DirectX\D3DRenderer.h"
#include "OpenGL\GLRenderer.h"

#include "Core\SubayakuCore.h"
#include "Input\Keyboard.h"

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

		m_Window = new Window();

		if (!m_Window->Initialize(a_Context))
		{
			ErrorBox(L"Window Init Failure");
			return false;
		}

		ZipFile = std::make_unique<GrumpyZip::ZipFile>();

		if (!ZipFile->LoadZipFile(a_Context.PathToPak))
			return false;		

		if (!SwitchRenderer(a_Context))
			return false;

		m_InputManager = new InputManager();

		m_InputManager->Initialize();

		m_Scene = new Scene::Scene();

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
				//Process an event
				EventHandler::StaticClass()->Update();

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
				if (GetInputManager()->GetKeyboard()->IsKeyJustDown(SUBA_KEY_F1))
				{
					m_Context.RDevice = RenderDevice::DirectX;
					SwitchRenderer(m_Context);
				}

				if (GetInputManager()->GetKeyboard()->IsKeyJustDown(SUBA_KEY_F2))
				{
					m_Context.RDevice = RenderDevice::OpenGL;
					SwitchRenderer(m_Context);
				}

				TimeSinceStart = (long)(std::chrono::duration_cast<std::chrono::milliseconds>
					(std::chrono::system_clock::now().time_since_epoch()).count() - m_StartTime);

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
		SafeDelete(m_InputManager);

		m_Scene->ClearScene();
		SafeDelete(m_Scene);

		SafeDelete(m_Renderer);

		SafeDelete(m_Window);

		ZipFile.reset();

		EventHandler::Release();
		return true;
	}
	
	bool Engine::SwitchRenderer(SEngineContext &a_Context)
	{
		//Shutdown the old renderer
		SafeDelete(m_Renderer);

		Graphics::SRendererDesc rendererDesc{};
		rendererDesc.Handle = static_cast<Window*>(GetWindow())->GetHandle();
		rendererDesc.Width = a_Context.Width;
		rendererDesc.Height = a_Context.Height;

		switch (a_Context.RDevice)
		{
		case RenderDevice::OpenGL:
			m_Renderer = new Graphics::OpenGL::GLRenderer(this);
			break;

		case RenderDevice::DirectX:
			m_Renderer = new Graphics::DirectX::D3DRenderer(this);
			break;
		
		default:
			ErrorBox(L"Unknown Renderer");
			return false;
		}

		if (!m_Renderer->Initialize(rendererDesc))
		{
			ErrorBox(L"Renderer Init Failure");
			return false;
		}

		if(m_Scene != nullptr)
			m_Scene->ReloadForRendering();

		return true;
	}

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