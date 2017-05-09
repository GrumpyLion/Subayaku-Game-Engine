#include "D3DRenderFactory.h"
#include "D3DTexture.h"
#include "D3DMesh.h"
#include "D3DShader.h"
#include "D3DShaderBuffer.h"

#include "Graphics\Loaders\BMP.h"
#include "Graphics\Loaders\TGA.h"

#include "Utilities\Utilities.h"
#include "Graphics\Loaders\AssimpLoader.h"

namespace Graphics
{
	namespace DirectX
	{
		std::unique_ptr<IMesh> D3DRenderFactory::CreateMesh(SMeshDesc a_Desc)
		{
			auto temp = std::make_unique<D3DMesh>();

			LoadAssimpObj(a_Desc);
			temp->Initialize(a_Desc);

			return std::move(temp);
		}

		std::unique_ptr<ITexture> D3DRenderFactory::CreateTexture(STextureDesc a_Desc)
		{
			auto temp = std::make_unique<D3DTexture>();

			std::string extension = GetExtension(a_Desc.FilePath);
			ToLowerCase(extension);

			if (extension == "tga")
			{
				TGA tga = TGA(a_Desc);

				if (!temp->Initialize(a_Desc))
				{
					return nullptr;
				}
				return std::move(temp);
			}
			else if (extension == "bmp")
			{
				BMP tga = BMP(a_Desc);

				if (!temp->Initialize(a_Desc))
				{
					return nullptr;
				}
				return temp;
			}
			else
			{
				return nullptr;
			}
			return nullptr;
		}

		std::unique_ptr<IShader> D3DRenderFactory::CreateShader(SShaderDesc a_Desc)
		{
			auto temp = std::make_unique<D3DShader>();

			if (temp->Initialize(a_Desc))
				return std::move(temp);

			return nullptr;
		}

		std::unique_ptr<IShaderBuffer> D3DRenderFactory::CreateShaderBuffer(SShaderBufferDesc a_Desc)
		{
			auto temp = std::make_unique<D3DShaderBuffer>();

			if (temp->Initialize(a_Desc))
				return std::move(temp);

			return nullptr;
		}
	}
}