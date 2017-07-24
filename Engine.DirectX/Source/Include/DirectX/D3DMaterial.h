#pragma once

#include "D3DShaderContainer.h"
#include "D3DShaderBuffer.h"
#include "D3DTexture.h"

#include "Graphics\Interfaces\IMaterial.h"
#include "Graphics\Material.h"

#include "Scene\GameObject\GameObject.h"
#include "Scene\GameObject\Components\Transformation.h"


#include <unordered_map>
#include <memory>

namespace Graphics
{
	namespace DirectX
	{
		class D3DRenderer;

		class D3DMaterial : public IMaterial
		{
		private:
			std::unordered_map<EShaderStage, std::unique_ptr<D3DShaderContainer>> m_ShaderContainers;
			Scene::Transformation *m_ParentTransform = nullptr;

			D3DRenderer *m_Renderer = nullptr;

			std::unordered_map<std::string, D3DTexture*> m_Textures;

		public:
			bool Initialize(Material *a_Material, IRenderer *a_Renderer) final;
			bool Bind() final;
			
			D3DShaderContainer *GetContainer();
		};
	}
}