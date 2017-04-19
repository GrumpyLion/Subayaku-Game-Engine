#pragma once

#include <unordered_map>
#include "GLEShaderTypes.h"

namespace Graphics
{
	class Material;

	namespace OpenGL
	{
		class GLShaderContainer;
		class GLRenderer;

		class GLMaterial
		{
		private:
			GLShaderContainer *m_Container = nullptr;
			GLRenderer *m_Renderer = nullptr;

		public:
			~GLMaterial();

			bool Initialize(Material *a_Material);
			void Bind();
			GLShaderContainer *GetContainer();
		};
	}
}