#include "D3DRenderFactory.h"
#include "D3DTexture.h"

#include "Graphics\Loaders\BMP.h"
#include "Graphics\Loaders\TGA.h"

#include "Utilities\Utilities.h"
#include "Graphics\Loaders\AssimpLoader.h"

namespace Graphics
{
	namespace DirectX
	{
		D3DMesh *D3DRenderFactory::CreateMesh(SMeshDesc a_Desc)
		{
			D3DMesh *temp = new D3DMesh();

			LoadAssimpObj(a_Desc);
			temp->Initialize(a_Desc);

			return temp;
		}

		ITexture *D3DRenderFactory::CreateTexture(STextureDesc a_Desc)
		{
			D3DTexture *temp = new D3DTexture();

			std::string extension = GetExtension(a_Desc.FilePath);
			ToLowerCase(extension);

			if (extension == "tga")
			{
				TGA tga = TGA(a_Desc);

				if (!temp->Initialize(a_Desc))
				{
					delete temp;
					return nullptr;
				}
				return temp;
			}
			else if (extension == "bmp")
			{
				BMP tga = BMP(a_Desc);

				if (!temp->Initialize(a_Desc))
				{
					delete temp;
					return nullptr;
				}
				return temp;
			}
			else
			{
				delete temp;
				return nullptr;
			}
			return nullptr;
		}
	}
}