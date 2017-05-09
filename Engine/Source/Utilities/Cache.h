#pragma once

#include <unordered_map>
#include <string>

#include "Graphics\Cache\STextureDesc.h"
#include "Graphics\Cache\SMeshDesc.h"
#include "Graphics\Cache\SShaderDesc.h"
#include "Graphics\Cache\SShaderBufferDesc.h"

#include "Graphics\Interface\IRenderFactory.h"
#include "Graphics\Interface\IMesh.h"
#include "Graphics\Interface\IShader.h"
#include "Graphics\Interface\ITexture.h"
#include "Graphics\Interface\IShaderBuffer.h"

#include <memory>

namespace Core
{
	class Cache
	{
	private:
		std::unordered_map<std::string, std::unique_ptr<Graphics::ITexture>> m_Textures;
		std::unordered_map<std::string, std::unique_ptr<Graphics::IMesh>> m_Meshes;
		std::unordered_map<std::string, std::unique_ptr<Graphics::IShader>> m_Shaders;
		std::unordered_map<std::string, std::unique_ptr<Graphics::IShaderBuffer>> m_ShaderBuffers;

		std::unique_ptr<Graphics::IRenderFactory> m_RenderFactory = nullptr;

	public:
		void Initialize(std::unique_ptr<Graphics::IRenderFactory> a_Factory);
		
		Graphics::ITexture* LoadTexture(Graphics::STextureDesc &a_Desc);
		Graphics::IMesh* LoadMesh(Graphics::SMeshDesc &a_Desc);
		Graphics::IShader* LoadShader(Graphics::SShaderDesc &a_Desc);
		Graphics::IShaderBuffer* LoadShaderBuffer(Graphics::SShaderBufferDesc &a_Desc);
	};
}