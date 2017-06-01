#pragma once

#include <d3d11.h>
#include "Graphics\Interfaces\IMesh.h"

namespace Graphics
{
	namespace DirectX
	{
		class D3DRenderer;

		class D3DMesh : public IMesh
		{
		private:
			bool ShouldCull = true;
			bool HasIndices = true;

			ID3D11Buffer
				*m_VertexBuffer = nullptr, *m_NormalBuffer = nullptr,
				*m_UVBuffer = nullptr, *m_IndexBuffer = nullptr,
				*m_TangentBuffer = nullptr, *m_BitangentBuffer = nullptr;

			ID3D11InputLayout *m_Layout = nullptr;

			D3DRenderer *m_Renderer = nullptr;
			unsigned int m_Count = 0;

			enum Data 
			{
				POSITION,
				NORMAL,
				TEXCOORD,
				TANGENT,
				BITANGENT
			};

		public:
			~D3DMesh();

			bool Initialize(SMeshDesc &a_Desc, IRenderer *a_Renderer) override;
			void Bind() override;
			void Unbind() override;
			unsigned int GetCount() override;
		};
	}
}