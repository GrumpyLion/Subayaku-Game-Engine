#include "Graphics\Utilities\GraphicsCache.h"

namespace Graphics
{
	Graphics::ITexture* GraphicsCache::LoadTexture(Graphics::STextureDesc &a_Desc)
	{
		if (a_Desc.FilePath.empty())
			return nullptr;

		auto temp = m_Textures.find(a_Desc.FilePath);

		//If object not already added then create it.
		if (temp != m_Textures.end())
		{
			return temp->second.get();
		}
		else
		{
			if (m_CreateTexture == nullptr)
				return nullptr;

			auto texture = m_CreateTexture();

			if (!texture->Initialize(a_Desc, m_Renderer))
			{
				LogErr("Error while loading Texture File [%s] in Cache\n", a_Desc.FilePath);
				return nullptr;
			}

			////Clear memory
			//a_Desc.PixelData.resize(0);
			//a_Desc.PixelData.clear();

			m_Textures[a_Desc.FilePath] = std::move(texture);

			return m_Textures[a_Desc.FilePath].get();
		}
	}

	Graphics::IMesh* GraphicsCache::LoadMesh(Graphics::SMeshDesc &a_Desc)
	{
		if (a_Desc.FilePath.empty())
			return nullptr;

		auto temp = m_Meshes.find(a_Desc.FilePath);

		//If object not already added then create it.
		if (temp != m_Meshes.end())
		{
			return temp->second.get();
		}
		else
		{
			if (m_CreateMesh == nullptr)
				return nullptr;

			auto mesh = m_CreateMesh();

			if (!mesh->Initialize(a_Desc, m_Renderer))
			{
				LogErr("Error while loading Mesh File [%s] in Cache\n", a_Desc.FilePath);
				return nullptr;
			}

			//Clear memory
			a_Desc.Bitangents.resize(0);
			a_Desc.Bitangents.shrink_to_fit();

			a_Desc.Tangents.resize(0);
			a_Desc.Tangents.shrink_to_fit();
			
			a_Desc.Normals.resize(0);
			a_Desc.Normals.shrink_to_fit();

			a_Desc.TexCoords.resize(0);
			a_Desc.TexCoords.shrink_to_fit();

			a_Desc.Vertices.resize(0);
			a_Desc.Vertices.shrink_to_fit();

			a_Desc.Indices.resize(0);
			a_Desc.Indices.shrink_to_fit();

			m_Meshes[a_Desc.FilePath] = std::move(mesh);

			return m_Meshes[a_Desc.FilePath].get();
		}
	}

	Graphics::IShader* GraphicsCache::LoadShader(Graphics::SShaderDesc &a_Desc)
	{
		if (a_Desc.FilePath.empty())
			return nullptr;

		auto temp = m_Shaders.find(a_Desc.FilePath);

		//If object not already added then create it.
		if (temp != m_Shaders.end())
		{
			return temp->second.get();
		}
		else
		{
			if (m_CreateShader == nullptr)
				return nullptr;

			auto container = m_CreateShader();

			if (!container->Initialize(a_Desc, m_Renderer))
			{
				LogErr("Error while loading Shader File [%s] in Cache\n", a_Desc.FilePath);
				return nullptr;
			}

			m_Shaders[a_Desc.FilePath] = std::move(container);

			return m_Shaders[a_Desc.FilePath].get();
		}
	}

	Graphics::IShaderBuffer* GraphicsCache::LoadShaderBuffer(Graphics::SShaderBufferDesc &a_Desc)
	{
		if (a_Desc.BufferName.empty())
			return nullptr;

		auto temp = m_ShaderBuffers.find(a_Desc.BufferName);

		//If object not already added then create it.
		if (temp != m_ShaderBuffers.end())
		{
			return temp->second.get();
		}
		else
		{
			if (m_CreateShaderBuffer == nullptr)
				return nullptr;

			auto buffer = m_CreateShaderBuffer();

			if (!buffer->Initialize(a_Desc, m_Renderer))
			{
				LogErr("Error while creating Shaderbuffer [%s] in Cache\n", a_Desc.BufferName);
				return nullptr;
			}

			m_ShaderBuffers[a_Desc.BufferName] = std::move(buffer);

			return m_ShaderBuffers[a_Desc.BufferName].get();
		}
	}

}