#pragma once

#include <unordered_map>
#include "GLShaderContainer.h"
#include "Graphics\Interfaces\IMaterial.h"
#include <memory>

namespace Graphics
{
	class Material;

	namespace OpenGL
	{
		class GLShaderContainer;
		class GLRenderer;
		class GLTexture;

		class GLMaterial : public IMaterial
		{
		private:
			std::unique_ptr<GLShaderContainer> m_Container = nullptr;
			Scene::Transformation *m_ParentTransform = nullptr;

			GLRenderer *m_Renderer = nullptr;

			std::unordered_map<std::string, GLTexture*> m_Textures;

		public:
			bool Initialize(Material *a_Material, IRenderer *a_Renderer) final;
			void Bind() final;

			GLShaderContainer *GetContainer();
		};
	}
}