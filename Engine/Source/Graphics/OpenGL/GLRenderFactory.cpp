#include "GLRenderFactory.h"

#include "Utilities\Utilities.h"

#include "GLTexture.h"
#include "GLMesh.h"
#include "GLShader.h"
#include "GLShaderBuffer.h"

#include "Graphics\Loaders\BMP.h"
#include "Graphics\Loaders\TGA.h"
#include "Graphics\Loaders\AssimpLoader.h"

namespace Graphics
{
	namespace OpenGL
	{
		std::unique_ptr<IMesh> GLRenderFactory::CreateMesh(SMeshDesc a_Desc)
		{
			auto temp = std::make_unique<GLMesh>();

			LoadAssimpObj(a_Desc);
			temp->Initialize(a_Desc);

			return std::move(temp);
		}

		std::unique_ptr<ITexture> GLRenderFactory::CreateTexture(STextureDesc a_Desc)
		{
			auto temp = std::make_unique<GLTexture>();
			
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
				return std::move(temp);
			}
			else
			{
				return nullptr;
			}

			return nullptr;
		}

		std::unique_ptr<IShader> GLRenderFactory::CreateShader(SShaderDesc a_Desc)
		{
			auto temp = std::make_unique<GLShader>();

			if (temp->Initialize(a_Desc))
				return std::move(temp);			

			return nullptr;
		}

		std::unique_ptr<IShaderBuffer> GLRenderFactory::CreateShaderBuffer(SShaderBufferDesc a_Desc)
		{
			auto temp = std::make_unique<GLShaderBuffer>();

			if (temp->Initialize(a_Desc))
				return std::move(temp);

			return nullptr;
		}
	}
}