#pragma once

#include <Sol\sol.hpp>
#include "Interface\IComponent.h"

namespace Scene
{
	class CScriptComponent : public IComponent
	{
	private:
		sol::state m_Lua;

	public:
		bool Initialize(GameObject *a_Parent, std::string a_FilePath);

		void Update() override;
	};
}