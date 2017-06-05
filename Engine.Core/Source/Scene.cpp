#include "Scene\Scene.h"
#include "Utilities\Utilities.h"

#include "Graphics\Descriptions\SEntityDesc.h"

#include "Graphics\Material.h"
#include "Graphics\Primitives.h"

namespace Scene
{
	bool Scene::Initialize()
	{
		auto ptr = InstantiateGameObject("Camera");

		auto camera = std::make_unique<CCamera>();
		camera->Initialize(ptr, 70.0f, 1, 5000.0f);

		ptr->AddComponent(std::move(camera));

		auto script = std::make_unique<CScriptComponent>();
		script->Initialize(ptr, "Assets/Scripts/Camera.lua");

		ptr->AddComponent(std::move(script));

		auto trans = std::make_unique<Transformation>();
		trans->Position = Vector3f(0, 0, 0);
		trans->Scale = Vector3f(15, 15, 15);

		ptr = InstantiateGameObject("Water", std::move(trans));

		auto mesh = std::make_unique<CMeshRenderer>();

		auto tempMat = std::make_unique<Graphics::Material>();
		tempMat->TextureFilter = Graphics::ETextureFilter::NEAREST;

		Graphics::STextureDesc texInfo;
		texInfo.RegisterIndex = 0;
		texInfo.UniformName = "uNoise";
		texInfo.FilePath = "Assets/Textures/Noise.tga";
		tempMat->AddTexture(texInfo);

		texInfo.RegisterIndex = 1;
		texInfo.UniformName = "uColor";
		texInfo.FilePath = "Assets/Textures/Colormap.tga";
		tempMat->AddTexture(texInfo);

		tempMat->AddShader("Terrain.vs");
		tempMat->AddShader("Terrain.fs");
		
		Graphics::SMeshDesc desc{};
		Graphics::Primitives::GetPlaneTri(desc, 100, 0, 100);
		desc.Mode = Graphics::EMeshPrimitive::TRIANGLES;
		desc.HasIndices = true;
		desc.FilePath = "Primitive";

		mesh->Initialize(ptr, desc, std::move(tempMat));
		ptr->AddComponent(std::move(mesh));

		trans = std::make_unique<Transformation>();
		trans->Position = Vector3f(10, -10, 0);
		trans->Scale = Vector3f(1, 1, 1);		

		ptr = InstantiateGameObject("Terrain", std::move(trans));

		mesh = std::make_unique<CMeshRenderer>();

		tempMat = std::make_unique<Graphics::Material>();
		tempMat->TextureFilter = Graphics::ETextureFilter::NEAREST;

		tempMat->AddShader("Test.vs");
		tempMat->AddShader("Test.fs");
		
		ZeroMemory(&desc, sizeof(Graphics::SMeshDesc));
		desc.HasIndices = true;
		desc.Mode = Graphics::EMeshPrimitive::TRIANGLES;
		desc.FilePath = "Assets/Models/teapot.obj";

		mesh->Initialize(ptr, desc, std::move(tempMat));
		ptr->AddComponent(std::move(mesh));

		script = std::make_unique<CScriptComponent>();
		script->Initialize(ptr, "Assets/Scripts/Test.lua");

		ptr->AddComponent(std::move(script));

		return true;
	}

	void Scene::Update()
	{
		for (auto &temp : m_GameObjects)
		{
			temp.second->Update();
		}
	}

	Scene::Scene()
	{
		m_Callback = std::bind(&Scene::Listener, this, std::placeholders::_1);

		//Used for detection
		Core::EventHandler::StaticClass()->Subscribe(m_Callback, Core::EEvents::SCENE_MESHCOMPONENT_ADDED);
		Core::EventHandler::StaticClass()->Subscribe(m_Callback, Core::EEvents::SCENE_MESHCOMPONENT_REMOVED);

		Core::EventHandler::StaticClass()->Subscribe(m_Callback, Core::EEvents::SCENE_CAMERACOMPONENT_ADDED);
		Core::EventHandler::StaticClass()->Subscribe(m_Callback, Core::EEvents::SCENE_CAMERACOMPONENT_REMOVED);
	}

	Scene::~Scene()
	{
		ClearScene();
		
		//Used for detection
		Core::EventHandler::StaticClass()->Unsubscribe(m_Callback, Core::EEvents::SCENE_MESHCOMPONENT_ADDED);
		Core::EventHandler::StaticClass()->Unsubscribe(m_Callback, Core::EEvents::SCENE_MESHCOMPONENT_REMOVED);

		Core::EventHandler::StaticClass()->Unsubscribe(m_Callback, Core::EEvents::SCENE_CAMERACOMPONENT_ADDED);
		Core::EventHandler::StaticClass()->Unsubscribe(m_Callback, Core::EEvents::SCENE_CAMERACOMPONENT_REMOVED);
	}

	bool Scene::AddGameObject(std::unique_ptr<GameObject> a_ToAdd)
	{
		if (a_ToAdd == nullptr)
		{
			LogErr("AddGameObject() GameObject is Null\n");
			return false;
		}
		
		if (m_GameObjects.find(a_ToAdd->Name) != m_GameObjects.end())
		{
			LogErr("GameObject [%s] is already added\n", a_ToAdd->Name.c_str());
			a_ToAdd = nullptr;
			return false;
		}

		printf("GameObject added %s\n", a_ToAdd->Name.c_str());
		m_GameObjects[a_ToAdd->Name] = std::move( a_ToAdd );
		return true;
	}

	void Scene::AddRenderable(GameObject *a_Parent, CMeshRenderer *a_Renderable)
	{
		if (CheckIfPointerIsInvalid(a_Parent))
		{
			LogErr("AddRenderable() GameObject is Null\n");
			return;
		}

		if (CheckIfPointerIsInvalid(a_Renderable))
		{
			LogErr("AddRenderable() Renderable is Null\n");
			return;
		}

		//Already added
		if (m_Renderables.find(a_Parent) != m_Renderables.end())
		{
			LogErr("AddRenderable() GameObject already added\n");
			return;
		}
		else
		{
			m_Renderables.insert(std::pair<GameObject*, CMeshRenderer*>(a_Parent, a_Renderable));
		}
	}

	void Scene::RemoveRenderable(GameObject *a_Parent)
	{
		if (CheckIfPointerIsInvalid(a_Parent))
		{
			LogErr("RemoveRenderable() GameObject is Null\n");
			return;
		}

		if (m_Renderables.find(a_Parent) != m_Renderables.end())
		{
			CMeshRenderer *temp = m_Renderables.find(a_Parent)->second;		
			m_Renderables.erase(a_Parent);
		}
		else
		{
			LogErr("RemoveRenderable() GameObject not found\n");
			return;
		}
	}

	void Scene::RemoveGameObject(std::string &a_Name)
	{
		if (m_GameObjects.find(a_Name) != m_GameObjects.end())
		{
			m_GameObjects.erase(a_Name);
		}
		else
		{
			LogErr("RemoveGameObject() GameObject does not exist\n");
		}
	}

	GameObject* Scene::InstantiateGameObject(std::string a_Name)
	{
		return InstantiateGameObject(a_Name, std::make_unique<Transformation>());
	}

	GameObject* Scene::InstantiateGameObject(std::string a_Name, std::unique_ptr<Transformation> a_Transform)
	{
		auto temp = std::make_unique<GameObject>();
		temp->Name = a_Name;

		auto ptr = temp.get();

		if (!AddGameObject(std::move(temp)))
			return nullptr;

		ptr->SetTransform(std::move(a_Transform));

		return ptr;
	}

	void Scene::ReloadForRendering()
	{
		if (m_Renderables.size() > 0)
		{
			for (auto &temp : m_Renderables)
			{
				temp.second->InitializeEntity();
			}
		}

		//Update Camera..
		Core::SEventDesc eventDesc{};

		eventDesc.Event = Core::EEvents::SCENE_CAMERACOMPONENT_ADDED;
		eventDesc.Description = m_Camera;

		Core::EventHandler::StaticClass()->AddEvent(eventDesc);
	}

	void Scene::ClearScene()
	{
		m_GameObjects.clear();
		m_Renderables.clear();
	}

	void Scene::Listener(Core::SEventDesc &a_Desc)
	{
		Graphics::SEntityDesc *entity = (Graphics::SEntityDesc*)a_Desc.Description;

		switch (a_Desc.Event)
		{
		case Core::EEvents::SCENE_MESHCOMPONENT_ADDED:
			AddRenderable(entity->Parent, entity->MeshRenderer);
			break;

		case Core::EEvents::SCENE_MESHCOMPONENT_REMOVED:
			RemoveRenderable(entity->Parent);
			break;

		case Core::EEvents::SCENE_CAMERACOMPONENT_ADDED:
			m_Camera = (CCamera*)a_Desc.Description;
			break;

		case Core::EEvents::SCENE_CAMERACOMPONENT_REMOVED:
			m_Camera = nullptr;
			break;
		}
	}

	void Scene::SetCamera(CCamera *a_Camera)
	{	m_Camera = a_Camera;	}
	
	CCamera* Scene::GetCamera()
	{	return m_Camera;	}

	std::unordered_map<GameObject*, CMeshRenderer*> Scene::GetRenderables()
	{	return m_Renderables;	}

}