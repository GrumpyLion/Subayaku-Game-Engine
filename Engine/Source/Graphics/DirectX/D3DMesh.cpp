#include "D3DMesh.h"

#include "D3DHelper.h"

#include "Core\Engine.h"

namespace Graphics
{
	namespace DirectX
	{
		D3DMesh::~D3DMesh()
		{
			NSafeRelease(m_VertexBuffer);
			NSafeRelease(m_IndexBuffer);
			NSafeRelease(m_NormalBuffer);
		}

		bool D3DMesh::Initialize(SMeshDesc &a_Desc)
		{
			m_Renderer = dynamic_cast<D3DRenderer*>(Core::Engine::StaticClass()->GetRenderer());

			//For the buffer we need the descriptions
			D3D11_BUFFER_DESC vertexBufferDesc{}, normalBufferDesc{}, indexBufferDesc{};
			D3D11_SUBRESOURCE_DATA vertexData{}, normalData{}, indexData{};

			vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			vertexBufferDesc.ByteWidth = sizeof(Vector3f) * a_Desc.Vertices.size();
			vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

			vertexData.pSysMem = a_Desc.Vertices.data();

			//Now we create the buffer
			if (Failed(m_Renderer->GetDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_VertexBuffer)))
				return false;

			normalBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			normalBufferDesc.ByteWidth = sizeof(Vector3f) * a_Desc.Normals.size();
			normalBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

			normalData.pSysMem = a_Desc.Normals.data();

			//Now we create the buffer
			if (Failed(m_Renderer->GetDevice()->CreateBuffer(&normalBufferDesc, &normalData, &m_NormalBuffer)))
				return false;

			indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
			indexBufferDesc.ByteWidth = sizeof(unsigned long) * a_Desc.Indices.size();
			indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

			m_Count = a_Desc.Indices.size();

			//Grab the data
			indexData.pSysMem = a_Desc.Indices.data();

			//Now we create the buffer
			if (Failed(m_Renderer->GetDevice()->CreateBuffer(&indexBufferDesc, &indexData, &m_IndexBuffer)))
				return false;

			return true;
		}

		void D3DMesh::Bind()
		{
			unsigned int stride = 0;
			unsigned int offset = 0;

			//Set vertex buffer stride and offset
			stride = sizeof(Vector3f);
			offset = 0;

			m_Renderer->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
			m_Renderer->GetDeviceContext()->IASetVertexBuffers(1, 1, &m_NormalBuffer, &stride, &offset);
			m_Renderer->GetDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
			m_Renderer->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		}

		void D3DMesh::Unbind()
		{

		}

		unsigned int D3DMesh::GetCount()
		{
			return m_Count;
		}
	}
}