#include "DirectX\D3DMesh.h"
#include "DirectX\D3DRenderer.h"
#include "DirectX\D3DHelper.h"

namespace Graphics
{
	namespace DirectX
	{
		D3DMesh::~D3DMesh()
		{
			SafeRelease(m_VertexBuffer);
			SafeRelease(m_TangentBuffer);
			SafeRelease(m_BitangentBuffer);
			SafeRelease(m_UVBuffer);
			SafeRelease(m_IndexBuffer);
			SafeRelease(m_NormalBuffer);
			SafeRelease(m_WorldMatrixBuffer);
			SafeRelease(m_Layout);
		}

		bool D3DMesh::Initialize(SMeshDesc &a_Desc, IRenderer *a_Renderer)
		{
			m_Renderer = static_cast<D3DRenderer*>(a_Renderer);

			ShouldCull = a_Desc.ShouldCull;

			//For the buffer we need the descriptions
			D3D11_BUFFER_DESC 
				vertexBufferDesc{}, normalBufferDesc{}, 
				texcoordBufferDesc{}, indexBufferDesc{},
				tangentBufferDesc{}, bitangentBufferDesc{};

			D3D11_SUBRESOURCE_DATA 
				vertexData{}, normalData{}, 
				uvData{}, indexData{},
				tangentData{}, bitangentData{};

			if (a_Desc.Vertices.size() > 0)
			{
				vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
				vertexBufferDesc.ByteWidth = (unsigned int)(sizeof(Vector3f) * a_Desc.Vertices.size());
				vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

				vertexData.pSysMem = a_Desc.Vertices.data();

				if (Failed(m_Renderer->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_VertexBuffer)))
					return false;
			}
			else
				return false;

			if (a_Desc.Normals.size() > 0)
			{
				normalBufferDesc.Usage = D3D11_USAGE_DEFAULT;
				normalBufferDesc.ByteWidth = (unsigned int)(sizeof(Vector3f) * a_Desc.Normals.size());
				normalBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

				normalData.pSysMem = a_Desc.Normals.data();

				if (Failed(m_Renderer->GetDevice()->CreateBuffer(&normalBufferDesc, &normalData, &m_NormalBuffer)))
					return false;
			}

			if (a_Desc.Tangents.size() > 0)
			{
				tangentBufferDesc.Usage = D3D11_USAGE_DEFAULT;
				tangentBufferDesc.ByteWidth = (unsigned int)(sizeof(Vector3f) * a_Desc.Tangents.size());
				tangentBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

				tangentData.pSysMem = a_Desc.Tangents.data();

				if (Failed(m_Renderer->GetDevice()->CreateBuffer(&tangentBufferDesc, &tangentData, &m_TangentBuffer)))
					return false;
			}

			if (a_Desc.Bitangents.size() > 0)
			{
				bitangentBufferDesc.Usage = D3D11_USAGE_DEFAULT;
				bitangentBufferDesc.ByteWidth = (unsigned int)(sizeof(Vector3f) * a_Desc.Bitangents.size());
				bitangentBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

				bitangentData.pSysMem = a_Desc.Bitangents.data();

				if (Failed(m_Renderer->GetDevice()->CreateBuffer(&bitangentBufferDesc, &bitangentData, &m_BitangentBuffer)))
					return false;
			}

			if (a_Desc.TexCoords.size() > 0)
			{
				texcoordBufferDesc.Usage = D3D11_USAGE_DEFAULT;
				texcoordBufferDesc.ByteWidth = (unsigned int)(sizeof(Vector2f) * a_Desc.TexCoords.size());
				texcoordBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

				uvData.pSysMem = a_Desc.TexCoords.data();

				if (Failed(m_Renderer->GetDevice()->CreateBuffer(&texcoordBufferDesc, &uvData, &m_UVBuffer)))
					return false;
			}

			if (a_Desc.Indices.size() > 0)
			{
				indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
				indexBufferDesc.ByteWidth = (unsigned int)(sizeof(unsigned long) * a_Desc.Indices.size());
				indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

				m_VertexCount = (unsigned int)a_Desc.Indices.size();

				indexData.pSysMem = a_Desc.Indices.data();

				if (Failed(m_Renderer->GetDevice()->CreateBuffer(&indexBufferDesc, &indexData, &m_IndexBuffer)))
					return false;
			}
			else
				m_VertexCount = (unsigned int)a_Desc.Vertices.size();

			return true;
		}

		void D3DMesh::AddInstance(Matrix4f *a_Transform)
		{
			// Create the buffer if not already done. Also make it 250 objects big 
			//
			if (m_WorldMatrixBuffer == nullptr)
			{
				m_InstanceCount = 250;
				m_Transforms.reserve(250);

				D3D11_BUFFER_DESC wmb{};
				wmb.Usage = D3D11_USAGE_DYNAMIC;
				wmb.ByteWidth = sizeof(Matrix4f) * m_InstanceCount;
				wmb.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				wmb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

				if (Failed(m_Renderer->GetDevice()->CreateBuffer(&wmb, nullptr, &m_WorldMatrixBuffer)))
					return;

				m_Transforms.insert(a_Transform);
			}
			else
			{
				// We're almost out of space ! Reallocate
				//
				if (m_Transforms.size() == m_InstanceCount - 1)
				{
					SafeRelease(m_WorldMatrixBuffer);

					m_InstanceCount += 250;
					m_Transforms.reserve(250);

					D3D11_BUFFER_DESC wmb{};
					wmb.Usage = D3D11_USAGE_DYNAMIC;
					wmb.ByteWidth = sizeof(Matrix4f) * m_InstanceCount;
					wmb.BindFlags = D3D11_BIND_VERTEX_BUFFER;
					wmb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

					if (Failed(m_Renderer->GetDevice()->CreateBuffer(&wmb, nullptr, &m_WorldMatrixBuffer)))
						return;

				}

				m_Transforms.insert(a_Transform);
			}
		}

		void D3DMesh::RemoveInstance(Matrix4f *a_Transform)
		{
			m_Transforms.erase(a_Transform);
		}

		void D3DMesh::Bind()
		{
			unsigned int stride = 0;
			unsigned int offset = 0;

			// Set vertex buffer stride and offset
			//
			stride = sizeof(Vector3f);
			offset = 0;
			
			// Update Matrices
			//

			std::vector<Matrix4f> matrices;
			matrices.reserve(m_Transforms.size());

			m_FrustumInstanceCount = 0;
			for (auto &temp : m_Transforms)
			{
				// Add Frustum culling
				//
				matrices.push_back(*temp);
				m_FrustumInstanceCount++;
			}

			D3D11_MAPPED_SUBRESOURCE mappedRessource{};
			void *dataPtr = nullptr;
			
			if (Failed(m_Renderer->GetDeviceContext()->Map(m_WorldMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedRessource)))
			{
				LogErr("World Matrix Map error");
				return;
			}

			dataPtr = mappedRessource.pData;
			
			memcpy(dataPtr, matrices.data(), m_FrustumInstanceCount * sizeof(Matrix4f));

			m_Renderer->GetDeviceContext()->Unmap(m_WorldMatrixBuffer, 0);

			// Need another stride
			//
			stride = sizeof(Matrix4f);
			m_Renderer->GetDeviceContext()->IASetVertexBuffers(Data::WMATRIX, 1, &m_WorldMatrixBuffer, &stride, &offset);

			// All have the size of Vector3
			//
			stride = sizeof(Vector3f);
			
			m_Renderer->GetDeviceContext()->IASetVertexBuffers(Data::POSITION, 1, &m_VertexBuffer, &stride, &offset);
			m_Renderer->GetDeviceContext()->IASetVertexBuffers(Data::NORMAL, 1, &m_NormalBuffer, &stride, &offset);
			m_Renderer->GetDeviceContext()->IASetVertexBuffers(Data::TANGENT, 1, &m_TangentBuffer, &stride, &offset);
			m_Renderer->GetDeviceContext()->IASetVertexBuffers(Data::BITANGENT, 1, &m_BitangentBuffer, &stride, &offset);
			
			stride = sizeof(Vector2f);
			m_Renderer->GetDeviceContext()->IASetVertexBuffers(Data::TEXCOORD, 1, &m_UVBuffer, &stride, &offset);
			
			m_Renderer->GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
			m_Renderer->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		}

		void D3DMesh::Unbind()
		{

		}
	}
}