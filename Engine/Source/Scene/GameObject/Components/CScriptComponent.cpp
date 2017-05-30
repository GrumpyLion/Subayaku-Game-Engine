#include "CScriptComponent.h"

#include "Core\Engine.h"
#include "Utilities\Cache.h"
#include "Input\InputManager.h"

//Type init
#include "Transformation.h"
#include "Scene\GameObject\GameObject.h"
#include "Input\Mouse.h"

#include "Math\Math.h"

namespace Scene
{
	bool CScriptComponent::Initialize(GameObject *a_Parent, std::string a_FilePath)
	{
		IComponent::Initialize(a_Parent);

		m_Lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math,
			sol::lib::table, sol::lib::string, sol::lib::bit32);

		//Type declaration

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

		m_Lua.new_usertype<Transformation>(
			"Transform",

			//Variables
			"Position", &Transformation::Position,
			"Rotation", &Transformation::Rotation,
			"Scale", &Transformation::Scale
			);		

		m_Lua.new_usertype<GameObject>(
			"GameObject",

			//Variables
			"Name", &GameObject::Name,
			"Transform", &GameObject::Transform
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

		m_Lua.script(std::string(reinterpret_cast<char*>(&Core::Engine::StaticClass()->GetCache()->GetZipFile()->GetFile(a_FilePath)->Data[0])));

		m_Lua.set("Parent", Parent);
		m_Lua.set("Transform", Parent->Transform);
		m_Lua.set("Mouse", Core::Engine::StaticClass()->GetInputManager()->GetMouse());

		m_Lua["Init"]();

		return true;
	}

	void CScriptComponent::Update()
	{
		m_Lua["Update"]();
	}
}