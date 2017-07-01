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
		CScriptComponent(GameObject *a_Parent)
			: IComponent(a_Parent) {	}

		bool Initialize(std::string a_FilePath);

		void Update() override;
	};
}