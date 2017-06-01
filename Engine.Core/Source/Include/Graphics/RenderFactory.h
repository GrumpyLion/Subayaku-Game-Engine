#pragma once

#include "Graphics\Descriptions\STextureDesc.h"
#include "Graphics\Descriptions\SMeshDesc.h"
#include "Graphics\Descriptions\SShaderDesc.h"
#include "Graphics\Descriptions\SShaderBufferDesc.h"

#include <memory>

namespace Graphics
{
	class IRenderer;

	template <typename TTexture, typename TMesh, typename TShader, typename TShaderBuffer>
	class RenderFactory
	{
	protected:
		IRenderer* m_Renderer = nullptr;

	public:
		void Initialize(IRenderer* a_Renderer)
		{		m_Renderer = a_Renderer;		}

		std::unique_ptr<TMesh> CreateMesh(SMeshDesc &a_Desc)
		{
			auto temp = std::make_unique<TMesh>();

			temp->Initialize(a_Desc, m_Renderer);

			return std::move(temp);
		}

		std::unique_ptr<TTexture> CreateTexture(STextureDesc &a_Desc)
		{
			auto temp = std::make_unique<TTexture>();
			temp->UniformName = a_Desc.UniformName;

			if (!temp->Initialize(a_Desc, m_Renderer))
			{
				return nullptr;
			}
			return std::move(temp);
		}

		std::unique_ptr<TShader> CreateShader(SShaderDesc &a_Desc)
		{
			auto temp = std::make_unique<TShader>();

			if (temp->Initialize(a_Desc, m_Renderer))
				return std::move(temp);

			return nullptr;
		}

		std::unique_ptr<TShaderBuffer> CreateShaderBuffer(SShaderBufferDesc &a_Desc)
		{
			auto temp = std::make_unique<TShaderBuffer>();

			if (temp->Initialize(a_Desc, m_Renderer))
				return std::move(temp);

			return nullptr;
		}
	};
	
}