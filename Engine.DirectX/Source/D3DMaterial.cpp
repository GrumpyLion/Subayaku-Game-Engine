#include "DirectX\D3DMaterial.h"
#include "DirectX\D3DHelper.h"
#include "DirectX\D3DRenderer.h"

namespace Graphics
{
	namespace DirectX
	{		
		bool D3DMaterial::Initialize(Material *a_Material, IRenderer *a_Renderer)
		{
			m_Renderer = static_cast<D3DRenderer*>(a_Renderer);

			m_ParentTransform = a_Material->ParentTransform;

			m_Container = std::make_unique<D3DShaderContainer>();

			if (!m_Container->Initialize(a_Material->Shaders, a_Renderer))
				return false;

			for (auto &temp : a_Material->Textures)
			{
				D3DTexture *tex = static_cast<D3DTexture*>(m_Renderer->GetCache()->LoadTexture(temp.second));

				if (CheckIfPointerIsInvalid(tex))
					return false;

				m_Textures.insert({ tex->UniformName, tex });
			}

			SShaderBufferDesc desc;
			desc.BufferSize = sizeof(ObjectBuffer);
			//The fifth index is reserved for the world matrix buffer
			desc.BufferIndex = 5;
			desc.BufferName = "World";

			m_ObjectBuffer = static_cast<D3DShaderBuffer*>(m_Renderer->GetCache()->LoadShaderBuffer(desc));

			if (m_ObjectBuffer == nullptr)
				return false;

			return true;
		}

		void D3DMaterial::Bind()
		{
			for (auto &temp : m_Textures)
			{
				temp.second->Bind();
			}

			////Bind constant buffer
			ObjectBuffer data{};

			Matrix4f temp;
			temp = Matrix4f::Identity();
			temp *= Matrix4f::Translate(m_ParentTransform->Position);
			temp *= Matrix4f::Scale(m_ParentTransform->Scale);
			temp *= Matrix4f::RotateX(m_ParentTransform->Rotation.x * DEGTORAD);
			temp *= Matrix4f::RotateY(m_ParentTransform->Rotation.y * DEGTORAD);
			temp *= Matrix4f::RotateZ(m_ParentTransform->Rotation.z * DEGTORAD);
			temp.Transpose();
			data.World = temp;

			m_ObjectBuffer->Bind(&data);

			m_Container->BindProgram();
		}

		D3DShaderContainer *D3DMaterial::GetContainer()
		{		return m_Container.get();		}
	}
}