#include "D3DMaterial.h"
#include "D3DHelper.h"
#include "D3DRenderer.h"

#include "Core\Engine.h"
#include "Utilities\Cache.h"
#include "Utilities\Utilities.h"
#include "Scene\GameObject\Components\Transformation.h"
#include "D3DShaderBuffer.h"

namespace Graphics
{
	namespace DirectX
	{		
		bool D3DMaterial::Initialize(Material *a_Material)
		{
			m_Renderer = static_cast<D3DRenderer*>(Core::Engine::StaticClass()->GetRenderer());

			m_Container = std::make_unique<D3DShaderContainer>();

			if (!m_Container->Initialize(a_Material->Shaders))
				return false;

			for (auto &temp : a_Material->GetTextures())
			{
				D3DTexture *tex = static_cast<D3DTexture*>(Core::Engine::StaticClass()->GetCache()->LoadTexture(temp.second));

				if (CheckIfPointerIsInvalid(tex))
					return false;

				m_Textures.insert({ temp.second.UniformName, tex });
			}

			SShaderBufferDesc desc;
			desc.BufferSize = sizeof(ObjectBuffer);
			//The fifth index is reserved for the world matrix buffer
			desc.BufferIndex = 5;
			desc.BufferName = "World";

			m_ObjectBuffer = static_cast<D3DShaderBuffer*>(Core::Engine::StaticClass()->GetCache()->LoadShaderBuffer(desc));

			if (m_ObjectBuffer == nullptr)
				return false;

			return true;
		}

		void D3DMaterial::Bind(Scene::GameObject *a_GameObject)
		{
			for (auto &temp : m_Textures)
			{
				temp.second->Bind();
			}

			//Bind constant buffer
			ObjectBuffer data{};

			Matrix4f temp;
			temp = Matrix4f::Identity();
			temp *= Matrix4f::Scale(a_GameObject->Transform->Scale);
			temp *= Matrix4f::Translate(a_GameObject->Transform->Position);
			temp *= Matrix4f::RotateX(a_GameObject->Transform->Rotation.x * DEGTORAD);
			temp *= Matrix4f::RotateY(a_GameObject->Transform->Rotation.y * DEGTORAD);
			temp *= Matrix4f::RotateZ(a_GameObject->Transform->Rotation.z * DEGTORAD);
			temp.Transpose();
			data.World = temp;

			m_ObjectBuffer->Bind(m_Renderer, &data);

			m_Container->BindProgram();
		}

		D3DShaderContainer *D3DMaterial::GetContainer()
		{		return m_Container.get();		}
	}
}