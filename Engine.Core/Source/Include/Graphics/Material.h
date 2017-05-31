#pragma once

#include <string>
#include <unordered_map>

#include "Graphics\Cache\SShaderContainerDesc.h"
#include "Graphics\Cache\STextureDesc.h"

#include "Scene\GameObject\Components\Transformation.h"

namespace Graphics
{
	class ITexture;

	class Material
	{		
	public:
		Scene::Transformation *ParentTransform = nullptr;

		std::unordered_map<std::string, STextureDesc> Textures;

		void AddShader(std::string a_FilePath);

		void AddTexture(STextureDesc &a_TextureInfo);
		void RemoveTexture(std::string a_FileName);

		ETextureFilter TextureFilter = ETextureFilter::NEAREST;

		Graphics::SShaderContainerDesc Shaders{};
	};
}