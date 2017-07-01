#include "Scene\Scene.h"
#include "Utilities\Utilities.h"

#include "Graphics\Descriptions\SEntityDesc.h"

#include "Graphics\Material.h"
#include "Graphics\Primitives.h"

#include "Scene\GameObject\Components\CLight.h"

namespace Scene
{
	bool Scene::Initialize()
	{	
		//Maybe replace this ?
		auto ptr = InstantiateGameObject("Scene", true);
		
		ptr->Transform->Position = Vector3f(0, 1, 0);

		auto script = static_cast<CScriptComponent*>(ptr->AddNewComponent(ComponentType::Script));
		script->Initialize("Assets/Scripts/Scene.lua");
		
		auto light = static_cast<CLight*>(ptr->AddNewComponent(ComponentType::Light));
		light->Initialize(Vector4f(1, 1, 1, 1), ELightType::Directional);

		return true;
	}

	void Scene::Update()
	{
		for (auto &temp : m_TickableGameObjects)
		{
			temp.second->Update();
		}
	}

	Scene::Scene()
	{
		m_Callback = [=](Core::SEventDesc& desc)
		{
			this->Listener(desc);
		};

		//Used for detection
		Core::EventHandler::StaticClass()->Subscribe(m_Callback, Core::EEvents::SCENE_MESHCOMPONENT_ADDED);
		Core::EventHandler::StaticClass()->Subscribe(m_Callback, Core::EEvents::SCENE_MESHCOMPONENT_REMOVED);

		Core::EventHandler::StaticClass()->Subscribe(m_Callback, Core::EEvents::SCENE_CAMERACOMPONENT_ADDED);
		Core::EventHandler::StaticClass()->Subscribe(m_Callback, Core::EEvents::SCENE_CAMERACOMPONENT_REMOVED);

		Core::EventHandler::StaticClass()->Subscribe(m_Callback, Core::EEvents::SCENE_LIGHT_ADDED);
		Core::EventHandler::StaticClass()->Subscribe(m_Callback, Core::EEvents::SCENE_LIGHT_REMOVED);

		Core::EventHandler::StaticClass()->Subscribe(m_Callback, Core::EEvents::SCENE_CLEAR);
	}

	Scene::~Scene()
	{
		ClearScene();
		
		//Used for detection
		Core::EventHandler::StaticClass()->Unsubscribe(m_Callback, Core::EEvents::SCENE_MESHCOMPONENT_ADDED);
		Core::EventHandler::StaticClass()->Unsubscribe(m_Callback, Core::EEvents::SCENE_MESHCOMPONENT_REMOVED);

		Core::EventHandler::StaticClass()->Unsubscribe(m_Callback, Core::EEvents::SCENE_CAMERACOMPONENT_ADDED);
		Core::EventHandler::StaticClass()->Unsubscribe(m_Callback, Core::EEvents::SCENE_CAMERACOMPONENT_REMOVED);
	
		Core::EventHandler::StaticClass()->Unsubscribe(m_Callback, Core::EEvents::SCENE_LIGHT_ADDED);
		Core::EventHandler::StaticClass()->Unsubscribe(m_Callback, Core::EEvents::SCENE_LIGHT_REMOVED);

		Core::EventHandler::StaticClass()->Unsubscribe(m_Callback, Core::EEvents::SCENE_CLEAR);
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

		if (a_ToAdd->IsTicking)
		{
			m_TickableGameObjects[a_ToAdd->Name] = a_ToAdd.get();
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
			m_TickableGameObjects.erase(a_Name);
			m_GameObjects.erase(a_Name);
		}
		else
		{
			LogErr("RemoveGameObject() GameObject does not exist\n");
		}
	}

	GameObject* Scene::InstantiateGameObject(std::string a_Name, bool a_IsTicking)
	{
		return InstantiateGameObject(a_Name, Transformation(), a_IsTicking);
	}

	GameObject* Scene::InstantiateGameObject(std::string a_Name, Transformation& a_Transform, bool a_IsTicking)
	{
		auto temp = std::make_unique<GameObject>();
		temp->Name = a_Name;
		temp->IsTicking = a_IsTicking;

		auto ptr = temp.get();

		temp->SetTransform(std::move(a_Transform));
		
		temp->Initialize();
		
		if (!AddGameObject(std::move(temp)))
			return nullptr;

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

		// Update Camera..
		Core::SEventDesc eventDesc{};

		eventDesc.Event = Core::EEvents::SCENE_CAMERACOMPONENT_ADDED;
		eventDesc.Description = m_Camera;

		Core::EventHandler::StaticClass()->AddEvent(eventDesc);
		
		// Directional Light..
		eventDesc.Event = Core::EEvents::SCENE_LIGHT_ADDED;
		eventDesc.Description = m_DirectionalLight;

		Core::EventHandler::StaticClass()->AddEvent(eventDesc);
	}

	void Scene::ClearScene()
	{
		m_Clearing = true;
		for (auto temp : m_Renderables)
			temp.second->Remove();

		m_Renderables.clear();
		m_GameObjects.clear();
		m_Clearing = false;
	}

	void Scene::Listener(Core::SEventDesc &a_Desc)
	{
		Graphics::SEntityDesc *entity = static_cast<Graphics::SEntityDesc*>(a_Desc.Description);

		switch (a_Desc.Event)
		{
		case Core::EEvents::SCENE_MESHCOMPONENT_ADDED:
			AddRenderable(entity->Parent, entity->MeshRenderer);
			break;

		case Core::EEvents::SCENE_MESHCOMPONENT_REMOVED:
			if(entity != nullptr && m_Renderables.size() > 0 && !m_Clearing)
				RemoveRenderable(entity->Parent);
			break;

		case Core::EEvents::SCENE_CAMERACOMPONENT_ADDED:
			m_Camera = (CCamera*)a_Desc.Description;
			break;

		case Core::EEvents::SCENE_CAMERACOMPONENT_REMOVED:
			m_Camera = nullptr;
			break;

		case Core::EEvents::SCENE_LIGHT_ADDED:
			m_DirectionalLight = (CLight*)a_Desc.Description;
			break;

		case Core::EEvents::SCENE_LIGHT_REMOVED:
			m_DirectionalLight = nullptr;
			break;

		case Core::EEvents::SCENE_CLEAR:
			ClearScene();
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