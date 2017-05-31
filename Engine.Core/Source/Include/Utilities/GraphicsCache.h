#pragma once

#include <unordered_map>
#include <string>
#include <GrumpyZip\ZipFile.h>

#include "Graphics\Cache\STextureDesc.h"
#include "Graphics\Cache\SMeshDesc.h"
#include "Graphics\Cache\SShaderDesc.h"
#include "Graphics\Cache\SShaderBufferDesc.h"

#include "Graphics\RenderFactory.h"

#include "Utilities.h"

#include <memory>

namespace Core
{
	template <typename TTexture, typename TMesh, typename TShader, typename TShaderBuffer>
	class GraphicsCache
	{
	private:
		std::unordered_map<std::string, std::unique_ptr<TTexture>> m_Textures;
		std::unordered_map<std::string, std::unique_ptr<TMesh>> m_Meshes;
		std::unordered_map<std::string, std::unique_ptr<TShader>> m_Shaders;
		std::unordered_map<std::string, std::unique_ptr<TShaderBuffer>> m_ShaderBuffers;

		Graphics::RenderFactory<TTexture, TMesh, TShader, TShaderBuffer>* m_RenderFactory = nullptr;

	public:

		void Initialize(Graphics::RenderFactory<TTexture, TMesh, TShader, TShaderBuffer>* a_Factory, Graphics::IRenderer *a_Renderer)
		{
			m_RenderFactory = a_Factory;
			m_RenderFactory->Initialize(a_Renderer);
		}
		
		TTexture* LoadTexture(Graphics::STextureDesc &a_Desc)
		{
			if (a_Desc.FilePath == "")
				return nullptr;

			auto temp = m_Textures.find(a_Desc.FilePath);

			if (temp != m_Textures.end())
			{
				return temp->second.get();
			}
			else
			{
				auto texture = m_RenderFactory->CreateTexture(a_Desc);

				if (texture == nullptr)
				{
					LogErr("Error while loading Texture File [%s] in Cache\n", a_Desc.FilePath);
					return nullptr;
				}

				m_Textures[a_Desc.FilePath] = std::move(texture);

				return m_Textures[a_Desc.FilePath].get();
			}
		}


		TMesh* LoadMesh(Graphics::SMeshDesc &a_Desc)
		{
			if (a_Desc.FilePath == "")
				return nullptr;

			auto temp = m_Meshes.find(a_Desc.FilePath);

			if (temp != m_Meshes.end())
			{
				return temp->second.get();
			}
			else
			{
				auto mesh = m_RenderFactory->CreateMesh(a_Desc);

				m_Meshes[a_Desc.FilePath] = std::move(mesh);

				return m_Meshes[a_Desc.FilePath].get();
			}
		}

		TShader* LoadShader(Graphics::SShaderDesc &a_Desc)
		{
			if (a_Desc.FilePath == "")
				return nullptr;

			auto temp = m_Shaders.find(a_Desc.FilePath);

			if (temp != m_Shaders.end())
			{
				return temp->second.get();
			}
			else
			{
				auto container = m_RenderFactory->CreateShader(a_Desc);

				if (container == nullptr)
				{
					LogErr("Error while loading Shader File [%s] in Cache\n", a_Desc.FilePath);
					return nullptr;
				}

				m_Shaders[a_Desc.FilePath] = std::move(container);

				return m_Shaders[a_Desc.FilePath].get();
			}
		}

		TShaderBuffer* LoadShaderBuffer(Graphics::SShaderBufferDesc &a_Desc)
		{
			auto temp = m_ShaderBuffers.find(a_Desc.BufferName);

			if (temp != m_ShaderBuffers.end())
			{
				return temp->second.get();
			}
			else
			{
				auto container = m_RenderFactory->CreateShaderBuffer(a_Desc);

				if (container == nullptr)
				{
					LogErr("Error while loading Shaderbuffer [%s] in Cache\n", a_Desc.BufferName);
					return nullptr;
				}

				m_ShaderBuffers[a_Desc.BufferName] = std::move(container);

				return m_ShaderBuffers[a_Desc.BufferName].get();
			}
		}
	};
}