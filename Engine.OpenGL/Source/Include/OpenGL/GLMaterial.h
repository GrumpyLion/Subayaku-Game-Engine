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
			GLRenderer *m_Renderer = nullptr;
			
			Scene::Transformation *m_ParentTransform = nullptr;

			std::unordered_map<EShaderStage, std::unique_ptr<GLShaderContainer>> m_ShaderContainers;
			std::unordered_map<std::string, GLTexture*> m_Textures;

		public:
			bool Initialize(Material *a_Material, IRenderer *a_Renderer) final;
			bool Bind() final;

			GLShaderContainer *GetContainer();
		};
	}
}