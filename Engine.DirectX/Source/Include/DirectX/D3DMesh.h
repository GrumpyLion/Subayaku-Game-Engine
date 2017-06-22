#pragma once

#include <d3d11.h>
#include "Graphics\Interfaces\IMesh.h"
#include <unordered_set>

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
				*m_TangentBuffer = nullptr, *m_BitangentBuffer = nullptr,
				*m_WorldMatrixBuffer = nullptr;

			ID3D11InputLayout *m_Layout = nullptr;

			std::unordered_set<Scene::CMeshRenderer*> m_Transforms;

			D3DRenderer *m_Renderer = nullptr;

			unsigned int m_VertexCount = 0;
			unsigned int m_InstanceCount = 0;
			unsigned int m_FrustumInstanceCount = 0;

			enum Data 
			{
				POSITION,
				NORMAL,
				TEXCOORD,
				TANGENT,
				BITANGENT,
				WMATRIX
			};

		public:
			~D3DMesh();

			bool Initialize(SMeshDesc &a_Desc, IRenderer *a_Renderer) final;
			
			void Bind() final;
			void Unbind() final;

			void AddInstance(Scene::CMeshRenderer *a_MeshRenderer);
			void RemoveInstance(Scene::CMeshRenderer *a_MeshRenderer);

			unsigned int GetVertexCount() final { return m_VertexCount;  };
			unsigned int GetInstanceCount() final { return m_InstanceCount; };
			unsigned int GetFrustumInstanceCount() final { return m_FrustumInstanceCount; };
		};
	}
}