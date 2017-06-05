#pragma once

#include <unordered_map>
#include <string>
#include <GrumpyZip\ZipFile.h>

#include "Graphics\Descriptions\STextureDesc.h"
#include "Graphics\Descriptions\SMeshDesc.h"
#include "Graphics\Descriptions\SShaderDesc.h"
#include "Graphics\Descriptions\SShaderBufferDesc.h"

#include "Graphics\Interfaces\ITexture.h"
#include "Graphics\Interfaces\IMesh.h"
#include "Graphics\Interfaces\IShader.h"
#include "Graphics\Interfaces\IShaderBuffer.h"

#include "Utilities\Utilities.h"

#include <memory>
#include <functional>

namespace Graphics
{
	class GraphicsCache
	{
	private:
		//Containers..
		std::unordered_map<std::string, std::unique_ptr<Graphics::ITexture>> m_Textures;
		std::unordered_map<std::string, std::unique_ptr<Graphics::IMesh>> m_Meshes;
		std::unordered_map<std::string, std::unique_ptr<Graphics::IShader>> m_Shaders;
		std::unordered_map<std::string, std::unique_ptr<Graphics::IShaderBuffer>> m_ShaderBuffers;

		//Lambdas..
		std::function<std::unique_ptr<Graphics::ITexture>()> m_CreateTexture;
		std::function<std::unique_ptr<Graphics::IMesh>()> m_CreateMesh;
		std::function<std::unique_ptr<Graphics::IShader>()> m_CreateShader;
		std::function<std::unique_ptr<Graphics::IShaderBuffer>()> m_CreateShaderBuffer;

		Graphics::IRenderer *m_Renderer = nullptr;

	public:
		GraphicsCache(Graphics::IRenderer *a_Renderer)
			: m_Renderer(a_Renderer)
		{		}
		
		void SetTextureCreator(std::function<std::unique_ptr<Graphics::ITexture>()> &a_Func)			{			m_CreateTexture = a_Func;		}

		void SetMeshCreator(std::function<std::unique_ptr<Graphics::IMesh>()> &a_Func)					{			m_CreateMesh = a_Func;			}

		void SetShaderCreator(std::function<std::unique_ptr<Graphics::IShader>()> &a_Func)				{			m_CreateShader = a_Func;		}

		void SetShaderBufferCreator(std::function<std::unique_ptr<Graphics::IShaderBuffer>()> &a_Func)	{			m_CreateShaderBuffer = a_Func;	}

		// Loads an Texture Object of the current renderer type.
		// 
		__declspec(dllexport) Graphics::ITexture* LoadTexture(Graphics::STextureDesc &a_Desc);

		// Loads an Mesh Object of the current renderer type.
		//
		__declspec(dllexport) Graphics::IMesh* LoadMesh(Graphics::SMeshDesc &a_Desc);

		// Loads an Shader Object of the current renderer type.
		//
		__declspec(dllexport) Graphics::IShader* LoadShader(Graphics::SShaderDesc &a_Desc);

		// Loads an ShaderBuffer Object of the current renderer type.
		//
		__declspec(dllexport) Graphics::IShaderBuffer* LoadShaderBuffer(Graphics::SShaderBufferDesc &a_Desc);

	};
}
