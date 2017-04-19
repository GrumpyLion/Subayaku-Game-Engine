#include "Scene.h"
#include "Utilities\Utilities.h"

#include "Core\Engine.h"
#include "Graphics\Interface\IRenderer.h"

#include "GameObject\GameObject.h"
#include "GameObject\Components\Transformation.h"
#include "GameObject\Components\CMeshRenderer.h"
#include "GameObject\Components\CCamera.h"

namespace Scene
{
	bool Scene::Initialize()
	{
		GameObject *temp = new GameObject();
		temp->Transform = new Transformation();
		temp->Transform->Position = Vector3f(0, -40, -150);
		
		CMeshRenderer *mesh = new CMeshRenderer();
		temp->AddComponent(mesh);

		CCamera *camera = new CCamera();
		temp->AddComponent(camera);

		AddGameObject(temp);

		return true;
	}

	void Scene::Update()
	{
		for (auto &temp : m_GameObjects)
		{
			temp.second->Update();
		}
	}

	void Scene::Shutdown()
	{
		ClearScene();
	}

	bool Scene::AddGameObject(GameObject *a_ToAdd)
	{
		if (a_ToAdd == nullptr)
		{
			LogErr("AddGameObject() GameObject is Null");
			return false;
		}
		
		printf("GameObject added %s\n", a_ToAdd->Name.c_str());

		m_GameObjects.insert(std::pair<std::string, GameObject*>(a_ToAdd->Name, a_ToAdd));
		return true;
	}

	void Scene::AddRenderable(GameObject *a_Parent, CMeshRenderer *a_Renderable)
	{
		if (a_Parent == nullptr)
		{
			LogErr("AddRenderable() GameObject is Null");
			return;
		}

		if (a_Renderable == nullptr)
		{
			LogErr("AddRenderable() Renderable is Null");
			return;
		}

		//Already added
		if (m_Renderarbles.find(a_Parent) != m_Renderarbles.end())
		{
			LogErr("AddRenderable() GameObject already added");
			return;
		}
		else
		{
			m_Renderarbles.insert(std::pair<GameObject*, CMeshRenderer*>(a_Parent, a_Renderable));
			Core::Engine::StaticClass()->GetRenderer()->AddRenderable(a_Renderable);
		}
	}

	void Scene::RemoveRenderable(GameObject *a_Parent)
	{
		if (a_Parent == nullptr)
		{
			LogErr("RemoveRenderable() GameObject is Null");
			return;
		}

		if (m_Renderarbles.find(a_Parent) != m_Renderarbles.end())
		{
			CMeshRenderer *temp = m_Renderarbles.find(a_Parent)->second;			
			//The Renderer need to notice the deletion			
			Core::Engine::StaticClass()->GetRenderer()->RemoveRenderable(temp);
			m_Renderarbles.erase(a_Parent);
		}
		else
		{
			LogErr("RemoveRenderable() GameObject not found");
			return;
		}
	}

	void Scene::RemoveGameObject(std::string &a_Name)
	{
		if (m_GameObjects.find(a_Name) != m_GameObjects.end())
		{
			GameObject *temp = m_GameObjects.find(a_Name)->second;
			SHUTDOWN_AND_DELETE(temp);
			m_GameObjects.erase(a_Name);
		}
		else
		{
			LogErr("RemoveGameObject() GameObject does not exist");
		}
	}

	void Scene::ClearScene()
	{
		for (auto &temp : m_GameObjects)
		{
			SHUTDOWN_AND_DELETE(temp.second);
		}
		m_GameObjects.clear();
	}

	void Scene::SetCamera(CCamera *a_Camera)
	{	m_Camera = a_Camera;	}
	
	CCamera* Scene::GetCamera()
	{	return m_Camera;	}

	std::unordered_map<GameObject*, CMeshRenderer*> Scene::GetRenderables()
	{	return m_Renderarbles;	}

}