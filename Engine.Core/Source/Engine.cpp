#include "Core\Engine.h"
#include <chrono>
#include <thread>

#include "Core\SubayakuCore.h"
#include "Input\Keyboard.h"
#include "Graphics\Interfaces\IRenderer.h"

#include "Utilities\FileSystem.h"
#include "Bullet\btBulletDynamicsCommon.h"

typedef Graphics::IRenderer*(__stdcall *CreateRenderer)(Core::Engine *a_Engine);
typedef Scene::Scene *(__stdcall *CreateScene)();

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
	
	bool Engine::LoadSceneFromDLL()
	{
		HINSTANCE hGetProcIDDLL = nullptr;

		hGetProcIDDLL = LoadLibrary(L"SceneAsembly.dll");

		if (hGetProcIDDLL == nullptr)
			return false;

		CreateScene funci = (CreateScene)GetProcAddress(hGetProcIDDLL, "CreateScene");
		if (!funci)
		{
			std::cout << "Could not find CreateScene method" << std::endl;
			return false;
		}

		m_Scene = funci();

		if (m_Scene == nullptr)
			return false;

		return true;
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

		// Disable this for debug loading
		//FileSystem::StaticClass()->InitializeZipFile("Assets.pak");

		if (!SwitchRenderer(a_Context))
			return false;

		m_InputManager = new InputManager();

		m_InputManager->Initialize();

		if (!LoadSceneFromDLL())
		{
			m_Scene = new Scene::Scene();
			
			if (!m_Scene->InitializeFromLua())
			{
				ErrorBox(L"Scene Init Failure");
				return false;
			}
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

				if (GetInputManager()->GetKeyboard()->IsKeyJustDown(SUBA_KEY_F5))
				{
					Core::SEventDesc desc{};
					desc.Event = EEvents::SCENE_CLEAR;

					Core::EventHandler::StaticClass()->ForceEvent(desc);
					SwitchRenderer(m_Context);
					m_Scene->InitializeFromLua();
				}
				
				TimeSinceStart = (long)(std::chrono::duration_cast<std::chrono::milliseconds>
					(std::chrono::system_clock::now().time_since_epoch()).count() - m_StartTime);

				GetInputManager()->GetKeyboard()->Refresh();

				//Process an event
				EventHandler::StaticClass()->Update();
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

		EventHandler::StaticClass()->Release();
		FileSystem::StaticClass()->Shutdown();
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

		HINSTANCE hGetProcIDDLL = nullptr;

		switch (a_Context.RDevice)
		{
		case RenderDevice::OpenGL:
			hGetProcIDDLL = LoadLibrary(L"Engine.OpenGL.dll");

			if (!hGetProcIDDLL)
			{
				LogErr("Graphics DLL not found");
				return false;
			}
			break;

		case RenderDevice::DirectX:
			hGetProcIDDLL = LoadLibrary(L"Engine.DirectX.dll");

			if (!hGetProcIDDLL)
			{
				LogErr("Graphics DLL not found");
				return false;
			}
			break;
		
		default:
			ErrorBox(L"Unknown Renderer");
			return false;
		}

		CreateRenderer funci = (CreateRenderer)GetProcAddress(hGetProcIDDLL, "CreateRenderer");
		if (!funci)
		{
			std::cout << "could not locate the function" << std::endl;
			return false;
		}

		m_Renderer = funci(this);

		if (!m_Renderer->Initialize(rendererDesc))
		{
			ErrorBox(L"Renderer Init Failure");
			return false;
		}

		if(m_Scene != nullptr)
			m_Scene->ReloadForRendering();

		return true;
	}
}