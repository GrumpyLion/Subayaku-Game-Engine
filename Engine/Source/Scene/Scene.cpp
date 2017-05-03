#include "Scene.h"
#include "Utilities\Utilities.h"

#include "Core\Engine.h"
#include "Graphics\Interface\IRenderer.h"
#include "Graphics\Material.h"

#include "GameObject\GameObject.h"
#include "GameObject\Components\Transformation.h"
#include "GameObject\Components\CMeshRenderer.h"
#include "GameObject\Components\CCamera.h"
#include "GameObject\Components\CSprite.h"

namespace Scene
{
	bool Scene::Initialize()
	{
		GameObject *temp = new GameObject();
		temp->Transform = new Transformation();
		temp->Transform->Position = Vector3f(20, -20, -150);
		
		CMeshRenderer *mesh = new CMeshRenderer();

		Graphics::Material *tempMat = new Graphics::Material();
		tempMat->VertexShader = "Assets/Shaders/Test.vs";
		tempMat->FragmentShader = "Assets/Shaders/Test.fs";

		mesh->Initialize(temp, "Assets/Models/teapot.obj", tempMat);
		temp->AddComponent(mesh);

		CCamera *camera = new CCamera();
		camera->Initialize(temp, 60.0f, 0.1f, 100.0f);
		temp->AddComponent(camera);

		AddGameObject(temp);

		GameObject *temp2 = new GameObject();
		temp2->Name = "Sprite";
		temp2 ->Transform = new Transformation();
		temp2 ->Transform->Position = Vector3f(0, 0, 0);

		CSprite *sprite = new CSprite();
		sprite->Initialize(temp2, "Assets/Textures/Test.bmp");

		temp2->AddComponent(sprite);

		AddGameObject(temp2);
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
			LogErr("AddGameObject() GameObject is Null\n");
			return false;
		}
		
		if (m_GameObjects.find(a_ToAdd->Name) != m_GameObjects.end())
		{
			LogErr("GameObject [%s] is already added\n", a_ToAdd->Name.c_str());
			SHUTDOWN_AND_DELETE(a_ToAdd);
			return false;
		}

		LogErr("GameObject added %s\n", a_ToAdd->Name.c_str());

		m_GameObjects.insert(std::pair<std::string, GameObject*>(a_ToAdd->Name, a_ToAdd));
		return true;
	}

	void Scene::AddRenderable(GameObject *a_Parent, CMeshRenderer *a_Renderable)
	{
		if (a_Parent == nullptr)
		{
			LogErr("AddRenderable() GameObject is Null\n");
			return;
		}

		if (a_Renderable == nullptr)
		{
			LogErr("AddRenderable() Renderable is Null\n");
			return;
		}

		//Already added
		if (m_Renderarbles.find(a_Parent) != m_Renderarbles.end())
		{
			LogErr("AddRenderable() GameObject already added\n");
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
			LogErr("RemoveRenderable() GameObject is Null\n");
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
			LogErr("RemoveRenderable() GameObject not found\n");
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
			LogErr("RemoveGameObject() GameObject does not exist\n");
		}
	}

	void Scene::ClearScene()
	{
		for (auto &temp : m_GameObjects)
		{
			SHUTDOWN_AND_DELETE(temp.second);
		}
		m_GameObjects.clear();
		m_Renderarbles.clear();
	}

	void Scene::SetCamera(CCamera *a_Camera)
	{	m_Camera = a_Camera;	}
	
	CCamera* Scene::GetCamera()
	{	return m_Camera;	}

	std::unordered_map<GameObject*, CMeshRenderer*> Scene::GetRenderables()
	{	return m_Renderarbles;	}

}