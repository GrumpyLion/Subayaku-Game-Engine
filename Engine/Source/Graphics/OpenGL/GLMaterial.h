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
		class GLTexture;

		class GLMaterial
		{
		private:
			GLShaderContainer *m_Container = nullptr;
			GLRenderer *m_Renderer = nullptr;

			std::unordered_map<std::string, GLTexture*> m_Textures;
			std::unordered_map<std::string, float> m_FloatUniforms;
			std::unordered_map<std::string, bool> m_FoundUniforms;

		public:
			~GLMaterial();

			bool Initialize(Material *a_Material);
			void Bind();
			GLShaderContainer *GetContainer();
		};
	}
}