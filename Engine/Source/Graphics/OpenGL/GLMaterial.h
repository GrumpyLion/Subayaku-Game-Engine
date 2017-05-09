#pragma once

#include <unordered_map>
#include "GLShaderContainer.h"
#include <memory>

namespace Graphics
{
	class Material;

	namespace OpenGL
	{
		class GLShaderContainer;
		class GLRenderer;
		class GLTexture;

		class GLMaterial
		{
		private:
			std::unique_ptr<GLShaderContainer> m_Container = nullptr;

			GLRenderer *m_Renderer = nullptr;

			std::unordered_map<std::string, GLTexture*> m_Textures;
			std::unordered_map<std::string, float> m_FloatUniforms;

		public:
			bool Initialize(Material *a_Material);
			void Bind();
			GLShaderContainer *GetContainer();
		};
	}
}