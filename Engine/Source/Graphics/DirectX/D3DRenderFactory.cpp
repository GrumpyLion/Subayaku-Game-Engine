#include "D3DRenderFactory.h"

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
			return nullptr;
		}
	}
}