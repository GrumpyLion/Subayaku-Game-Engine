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
		auto temp2 = std::make_unique<GameObject>();
		temp2->Name = "Camera";
		temp2->Transform = std::make_unique<Transformation>();
		temp2->Transform->Position = Vector3f(0, 0, 0);
		
		auto ptr = temp2.get();
		auto camera = std::make_unique<CCamera>();
		camera->Initialize(ptr, 70.0f, 1, 5000.0f);

		temp2->AddComponent(std::move(camera));
		AddGameObject(std::move(temp2));

		auto temp = std::make_unique<GameObject>();
		temp->Name = "Penis";
		temp->Transform = std::make_unique<Transformation>();
		temp->Transform->Position = Vector3f(0, 0, 0);
		temp->Transform->Scale = Vector3f(150, 150, 150);

		ptr = temp.get();
		auto mesh = std::make_unique<CMeshRenderer>();

		auto tempMat = std::make_unique<Graphics::Material>();
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

		tempMat->Shaders.VertexShaderPath = "Test.vs";
		tempMat->Shaders.FragmentShaderPath = "Test.fs";
		tempMat->Shaders.ShaderContainerName = "Earth";

		mesh->Initialize(ptr, "Assets/Models/Koegel.obj", std::move(tempMat));
		temp->AddComponent(std::move(mesh));
		AddGameObject(std::move(temp));

		return true;
	}

	void Scene::Update()
	{
		for (auto &temp : m_GameObjects)
		{
			temp.second->Update();
		}
	}

	Scene::~Scene()
	{
		ClearScene();
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

		LogErr("GameObject added %s\n", a_ToAdd->Name.c_str());
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
			Core::Engine::StaticClass()->GetRenderer()->AddRenderable(a_Renderable);
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
			//The Renderer need to notice the deletion			
			Core::Engine::StaticClass()->GetRenderer()->RemoveRenderable(temp);
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

	void Scene::ClearScene()
	{
		m_GameObjects.clear();
		m_Renderables.clear();
	}

	void Scene::SetCamera(CCamera *a_Camera)
	{	m_Camera = a_Camera;	}
	
	CCamera* Scene::GetCamera()
	{	return m_Camera;	}

	std::unordered_map<GameObject*, CMeshRenderer*> Scene::GetRenderables()
	{	return m_Renderables;	}

}