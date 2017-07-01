#include "Scene\GameObject\Components\CScriptComponent.h"

#include "Core\Engine.h"
#include "Utilities\FileSystem.h"
#include "Input\InputManager.h"

//Type init
#include "Scene\Scene.h"
#include "Scene\GameObject\Components\Transformation.h"
#include "Scene\GameObject\Components\CMeshRenderer.h"
#include "Scene\GameObject\Components\CLight.h"
#include "Scene\GameObject\GameObject.h"

#include "Input\Mouse.h"

#include "Graphics\Material.h"
#include "Graphics\Primitives.h"

#include "Graphics\Descriptions\SMeshDesc.h"
#include "Graphics\Descriptions\STextureDesc.h"

#include "Math\Math.h"

#include "Graphics\Image.h"

#include <memory>

namespace Scene
{
	bool CScriptComponent::Initialize(std::string a_FilePath)
	{
		m_Lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math,
			sol::lib::table, sol::lib::string, sol::lib::bit32, sol::lib::io);

		//Type declaration

		m_Lua.new_usertype<Matrix4f>(
			"Matrix",
			"m11", &Matrix4f::m11, "m12", &Matrix4f::m12, "m13", &Matrix4f::m13, "m14", &Matrix4f::m14,
			"m21", &Matrix4f::m21, "m22", &Matrix4f::m22, "m23", &Matrix4f::m23, "m24", &Matrix4f::m24,
			"m31", &Matrix4f::m31, "m32", &Matrix4f::m32, "m33", &Matrix4f::m33, "m34", &Matrix4f::m34,
			"m41", &Matrix4f::m41, "m42", &Matrix4f::m42, "m43", &Matrix4f::m43, "m34", &Matrix4f::m44
			);

		m_Lua.new_usertype<Vector4f>(
			"Vector4f",
			sol::constructors<sol::types<>, sol::types<float, float, float, float>>(),
			"x", &Vector4f::x,
			"y", &Vector4f::y,
			"z", &Vector4f::z,
			"w", &Vector4f::w,
			"Normalize", &Vector4f::Normalize
			);

		m_Lua.new_usertype<Vector3f>(
			"Vector3f",
			sol::constructors<sol::types<>, sol::types<float, float, float>>(),
			"x", &Vector3f::x,
			"y", &Vector3f::y,
			"z", &Vector3f::z,
			"Normalize", &Vector3f::Normalize
			);

		m_Lua.new_usertype<Vector2f>(
			"Vector2f",
			sol::constructors<sol::types<>, sol::types<float, float>>(),
			"x", &Vector2f::x,
			"y", &Vector2f::y,
			"Normalize", &Vector2f::Normalize
			);

		auto overload = sol::overload(
			sol::resolve<GameObject*(std::string, bool)>(&Scene::InstantiateGameObject),
			sol::resolve<GameObject*(std::string, Transformation&, bool)>(&Scene::InstantiateGameObject)
		);

		m_Lua.new_usertype<Scene>(
			"Scene",
			
			"InstantiateGameObject", overload,
			"RemoveGameObject", &Scene::RemoveGameObject
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

			sol::constructors<sol::types<GameObject*>>(),
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

			"AddShader", &Graphics::Material::AddShader,
			"AddTexture", &Graphics::Material::AddTexture,
			"TextureFilter", &Graphics::Material::TextureFilter
			);

		auto meshOverload = sol::overload(
			sol::resolve<bool(std::string a_ModelLocation, Graphics::Material &a_Material)>(&CMeshRenderer::Initialize),
			sol::resolve<bool(Graphics::SMeshDesc &a_Desc, Graphics::Material &a_Material)>(&CMeshRenderer::Initialize)
		);

		m_Lua.new_usertype<CMeshRenderer>(
			"MeshRenderer",

			sol::constructors<sol::types<GameObject*>>(),

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
			sol::constructors<sol::types<GameObject*>>(),
			"Initialize", &CCamera::Initialize
			);

		m_Lua.new_usertype<GameObject>(
			"GameObject",

			//Variables
			"Name", &GameObject::Name,
			"IsTicking", &GameObject::IsTicking,
			"Transform", &GameObject::Transform,
			"GetModelTransform", &GameObject::GetModelTransform,

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
				},

			"AddLightComponent", [](GameObject* a_GameObject)
				{
					return static_cast<CLight*>(a_GameObject->AddNewComponent(ComponentType::Light));
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

		m_Lua.new_usertype<Core::Keyboard>(
			"Keyboard",
			"IsKeyDown", &Core::Keyboard::IsKeyDown,
			"IsKeyJustDown", &Core::Keyboard::IsKeyJustDown
			);

		m_Lua.new_usertype<Graphics::Image>(
			"Image", 
			sol::constructors<sol::types<std::string>>(),
			"GetPixelAt", &Graphics::Image::GetPixelAt
			);

		m_Lua.script(std::string(reinterpret_cast<char*>(&Core::FileSystem::StaticClass()->GetFile(a_FilePath)->Data[0])));


		//Set Variables
		m_Lua.set("Scene", Core::Engine::StaticClass()->GetScene());
		m_Lua.set("Parent", Parent);
		m_Lua.set("ParentTransform", Parent->Transform);
		m_Lua.set("Mouse", Core::Engine::StaticClass()->GetInputManager()->GetMouse());
		m_Lua.set("Keyboard", Core::Engine::StaticClass()->GetInputManager()->GetKeyboard());

		//Run init
		m_Lua["Init"]();

		return true;
	}

	void CScriptComponent::Update()
	{
		if(m_Lua["Update"]) m_Lua["Update"]();
	}
}