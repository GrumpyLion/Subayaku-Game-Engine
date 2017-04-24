#pragma once

#include "CMeshRenderer.h"

namespace Scene
{
	class CSprite : public CMeshRenderer
	{
	public:	
		bool Initialize(GameObject *a_Parent, const char* a_TexturePath);
		void Update() override;
	};
}