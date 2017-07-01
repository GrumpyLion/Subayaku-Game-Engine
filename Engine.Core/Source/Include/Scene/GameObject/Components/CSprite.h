#pragma once

#include "CMeshRenderer.h"

namespace Scene
{
	class CSprite : public CMeshRenderer
	{
	public:	
		CSprite(GameObject *a_Parent)
			: CMeshRenderer(a_Parent) {	}

		bool Initialize(const char* a_TexturePath);
		void Update() override;
	};
}