#include "GLRenderFactory.h"

#include "Utilities\Utilities.h"

#include "Graphics\Loaders\BMP.h"
#include "Graphics\Loaders\TGA.h"
#include "Graphics\Loaders\AssimpLoader.h"

namespace Graphics
{
	namespace OpenGL
	{

		IMesh *GLRenderFactory::CreateMesh(SMeshDesc a_Desc)
		{
			GLMesh *temp = new GLMesh();

			LoadAssimpObj(a_Desc);
			temp->Initialize(a_Desc);

			return temp;
		}

		GLTexture *GLRenderFactory::CreateTexture(STextureDesc a_Desc)
		{
			GLTexture *temp = new GLTexture();
			
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