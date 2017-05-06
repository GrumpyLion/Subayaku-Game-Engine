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

		GameObject *temp2 = new GameObject();
		temp2->Name = "Camera";
		temp2->Transform = new Transformation();
		temp2->Transform->Position = Vector3f(0, 0, 0);

		CCamera *camera = new CCamera();
		camera->Initialize(temp2, 70.0f, 0.1f, 700.0f);
		temp2->AddComponent(camera);

		AddGameObject(temp2);

		GameObject *temp = new GameObject();
		temp->Transform = new Transformation();
		temp->Transform->Position = Vector3f(0, 0, 0);
		temp->Transform->Scale = Vector3f(150, 150, 150);
		
		CMeshRenderer *mesh = new CMeshRenderer();

		Graphics::Material *tempMat = new Graphics::Material();
		tempMat->TextureFilter = Graphics::ETextureFilter::LINEAR;

		Graphics::STextureDesc texInfo;
		texInfo.RegisterIndex = 0;
		texInfo.UniformName = "uDay";
		texInfo.FilePath = "Assets/Textures/earth_day.tga";
		tempMat->AddTexture(texInfo);

		texInfo.RegisterIndex = 1;
		texInfo.UniformName = "uNight";
		texInfo.FilePath = "Assets/Textures/earth_night.tga";
		tempMat->AddTexture(texInfo);

		texInfo.RegisterIndex = 2;
		texInfo.UniformName = "uNormal";
		texInfo.FilePath = "Assets/Textures/earth_normal.tga";
		tempMat->AddTexture(texInfo);

		texInfo.RegisterIndex = 3;
		texInfo.UniformName = "uSpecular";
		texInfo.FilePath = "Assets/Textures/earth_specular.tga";
		tempMat->AddTexture(texInfo);

		texInfo.RegisterIndex = 4;
		texInfo.UniformName = "uClouds";
		texInfo.FilePath = "Assets/Textures/earth_clouds.tga";
		tempMat->AddTexture(texInfo);

		tempMat->VertexShader = "Test.vs";
		tempMat->FragmentShader = "Test.fs";

		mesh->Initialize(temp, "Assets/Models/kögel.obj", tempMat);
		temp->AddComponent(mesh);

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
		if (CheckIfPointerIsValid(a_ToAdd))
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
		if (CheckIfPointerIsValid(a_Parent))
		{
			LogErr("AddRenderable() GameObject is Null\n");
			return;
		}

		if (CheckIfPointerIsValid(a_Renderable))
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
		if (CheckIfPointerIsValid(a_Parent))
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