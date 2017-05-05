#pragma once

#include "D3DShaderContainer.h"
#include "D3DRenderer.h"

namespace Graphics
{
	namespace DirectX
	{
		class D3DMaterial
		{
		private:
			D3DShaderContainer *m_Container = nullptr;
			D3DRenderer *m_Renderer = nullptr;

		public:
			~D3DMaterial();
			bool Initialize(Material *a_Material);
			void Bind();
			D3DShaderContainer *GetContainer();
		};
	}
}