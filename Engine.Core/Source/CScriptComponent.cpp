#include "Scene\GameObject\Components\CScriptComponent.h"

#include "Core\Engine.h"
#include "Utilities\FileSystem.h"
#include "Input\InputManager.h"

//Type init
#include "Scene\Scene.h"
#include "Scene\GameObject\Components\Transformation.h"
#include "Scene\GameObject\Components\CMeshRenderer.h"
#include "Scene\GameObject\GameObject.h"

#include "Input\Mouse.h"

#include "Graphics\Material.h"
#include "Graphics\Primitives.h"

#include "Graphics\Descriptions\SMeshDesc.h"
#include "Graphics\Descriptions\STextureDesc.h"

#include "Math\Math.h"

#include <memory>

namespace Scene
{
	bool CScriptComponent::Initialize(GameObject *a_Parent, std::string a_FilePath)
	{
		IComponent::Initialize(a_Parent);

		m_Lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math,
			sol::lib::table, sol::lib::string, sol::lib::bit32);

		//Type declaration

		m_Lua.new_usertype<Vector4f>(
			"Vector4f",
			sol::constructors<sol::types<>, sol::types<float, float, float, float>>(),
			"x", &Vector4f::x,
			"y", &Vector4f::y,
			"z", &Vector4f::z,
			"w", &Vector4f::w
			);

		m_Lua.new_usertype<Vector3f>(
			"Vector3f",
			sol::constructors<sol::types<>, sol::types<float, float, float>>(),
			"x", &Vector3f::x,
			"y", &Vector3f::y,
			"z", &Vector3f::z
			);

		m_Lua.new_usertype<Vector2f>(
			"Vector2f",
			sol::constructors<sol::types<>, sol::types<float, float>>(),
			"x", &Vector2f::x,
			"y", &Vector2f::y
			);

		auto overload = sol::overload(
			sol::resolve<GameObject*(std::string)>(&Scene::InstantiateGameObject),
			sol::resolve<GameObject*(std::string, Transformation&)>(&Scene::InstantiateGameObject)
		);

		m_Lua.new_usertype<Scene>(
			"Scene",
			
			"InstantiateGameObject", overload
			);

		m_Lua.new_usertype<Transformation>(
			"Transform",

			//Variables
			"Position", &Transformation::Position,
			"Rotation", &Transformation::Rotation,
			"Scale", &Transformation::Scale
			);		

		m_Lua.new_usertype<CScriptComponent>(
			"ScriptComponent",

			"Initialize", &CScriptComponent::Initialize
			);


		// MeshRenderer Stuff
		m_Lua.new_usertype<Graphics::Primitives>(
			"Primitives",
			
			"GetPlaneTri", &Graphics::Primitives::GetPlaneTri,
			"GetPlane", &Graphics::Primitives::GetPlane,
			"GetSphere", &Graphics::Primitives::GetSphere

			);

		m_Lua.new_usertype<Graphics::STextureDesc>(
			"TextureDesc",

			"Filter", &Graphics::STextureDesc::Filter,
			"Format", &Graphics::STextureDesc::Format,
			"FilePath", &Graphics::STextureDesc::FilePath,
			"RegisterIndex", &Graphics::STextureDesc::RegisterIndex,
			"UniformName", &Graphics::STextureDesc::UniformName
			);

		m_Lua.new_usertype<Graphics::SMeshDesc>(
			"MeshDesc",

			"Mode", &Graphics::SMeshDesc::Mode,
			"ShouldCull", &Graphics::SMeshDesc::ShouldCull,
			"FilePath", &Graphics::SMeshDesc::FilePath,
			"HasIndices", &Graphics::SMeshDesc::HasIndices
			);

		m_Lua.new_usertype<Graphics::Material>(
			"Material",

			"ParentTransform", &Graphics::Material::ParentTransform,
			"AddShader", &Graphics::Material::AddShader,
			"AddTexture", &Graphics::Material::AddTexture,
			"TextureFilter", &Graphics::Material::TextureFilter
			);

		auto meshOverload = sol::overload(
			sol::resolve<bool(GameObject *a_Parent, std::string a_ModelLocation, Graphics::Material &a_Material)>(&CMeshRenderer::Initialize),
			sol::resolve<bool(GameObject *a_Parent, Graphics::SMeshDesc &a_Desc, Graphics::Material &a_Material)>(&CMeshRenderer::Initialize)
		);

		m_Lua.new_usertype<CMeshRenderer>(
			"MeshRenderer",

			"Initialize", meshOverload,

			"SetNewMaterial", [](CMeshRenderer* a_MeshRenderer)
			{
				auto temp = Graphics::Material{};
				a_MeshRenderer->SetMaterial(temp);

				return a_MeshRenderer->GetMaterial();
			},

			"GetMaterial", &CMeshRenderer::GetMaterial

			);

		m_Lua.new_usertype<CCamera>(
			"Camera",

			"Initialize", &CCamera::Initialize
			);

		m_Lua.new_usertype<GameObject>(
			"GameObject",

			//Variables
			"Name", &GameObject::Name,
			"Transform", &GameObject::Transform,

			//New Components
			"AddScriptComponent", [](GameObject* a_GameObject)
			{
				return static_cast<CScriptComponent*>(a_GameObject->AddNewComponent(ComponentType::Script));
			},

			"AddMeshRenderer", [](GameObject* a_GameObject)
			{
				return static_cast<CMeshRenderer*>(a_GameObject->AddNewComponent(ComponentType::MeshRenderer));
			},
		
			"AddCameraComponent", [](GameObject* a_GameObject)
			{
				return static_cast<CCamera*>(a_GameObject->AddNewComponent(ComponentType::Camera));
			}

			);

		m_Lua.new_usertype<Core::Mouse>(
			"Mouse",
			"x", &Core::Mouse::x,
			"y", &Core::Mouse::y,
			"xD", &Core::Mouse::xD,
			"yD", &Core::Mouse::yD,
			"LeftButton", &Core::Mouse::LeftButton,
			"RightButton", &Core::Mouse::RightButton
			);

		m_Lua.script(std::string(reinterpret_cast<char*>(&Core::FileSystem::StaticClass()->GetFile(a_FilePath)->Data[0])));


		//Set Variables
		m_Lua.set("Scene", Core::Engine::StaticClass()->GetScene());
		m_Lua.set("Parent", Parent);
		m_Lua.set("ParentTransform", Parent->Transform);
		m_Lua.set("Mouse", Core::Engine::StaticClass()->GetInputManager()->GetMouse());


		//Run init
		m_Lua["Init"]();

		return true;
	}

	void CScriptComponent::Update()
	{
		if(m_Lua["Update"]) m_Lua["Update"]();
	}
}