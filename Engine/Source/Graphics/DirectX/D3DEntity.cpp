#include "D3DEntity.h"

#include "Utilities\Utilities.h"
#include "Core\Engine.h"
#include "Scene\GameObject\GameObject.h"
#include "Scene\GameObject\Components\Transformation.h"
#include "Utilities\Cache.h"

#include "D3DRenderer.h"
#include "D3DMaterial.h"
#include "D3DMesh.h"


namespace Graphics
{
	namespace DirectX
	{
		D3DEntity::~D3DEntity()
		{
			SAFE_DELETE(m_Material);
			//SAFE_DELETE(m_Mesh);
		}

		bool D3DEntity::Initialize(SMeshDesc &a_Mesh, Material *a_Material, Scene::GameObject *a_Parent)
		{
			m_Parent = a_Parent;
			m_Renderer = dynamic_cast<D3DRenderer*>(Core::Engine::StaticClass()->GetRenderer());

			m_Material = new D3DMaterial();
			if (!m_Material->Initialize(a_Material))
				return false;


			m_Mesh = dynamic_cast<D3DMesh*>(Core::Engine::StaticClass()->GetCache()->LoadMesh(a_Mesh));

			//m_Mesh = new D3DMesh();
			//m_Mesh->Initialize(a_Mesh);

			return true;
		}

		void D3DEntity::Render()
		{
			m_Mesh->Bind();

			//Bind constant buffer
			D3D11_MAPPED_SUBRESOURCE mappedRessource{};
			MatrixBufferType *dataPtr = nullptr;
			unsigned int bufferNumber = 0;

			if (Failed(m_Renderer->GetDeviceContext()->Map(m_Material->GetContainer()->m_MatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedRessource)))
				return;

			dataPtr = (MatrixBufferType*)mappedRessource.pData;

			Matrix4f temp = m_Renderer->GetCamera()->ToProjectionMatrixLH();
			temp.Transpose();
			dataPtr->Projection = temp;

			temp = m_Renderer->GetCamera()->ToViewMatrixLH();
			temp.Transpose();
			dataPtr->View = temp;

			temp = Matrix4f::Identity();
			temp *= Matrix4f::Scale(m_Parent->Transform->Scale);
			temp *= Matrix4f::Translate(m_Parent->Transform->Position * Vector3f(-1,1,1));
			temp *= Matrix4f::RotateX(m_Parent->Transform->Rotation.x * DEGTORAD);
			temp *= Matrix4f::RotateY(m_Parent->Transform->Rotation.y * DEGTORAD);
			temp *= Matrix4f::RotateZ(m_Parent->Transform->Rotation.z * DEGTORAD);
			temp.Transpose();
			dataPtr->World = temp;

			m_Renderer->GetDeviceContext()->Unmap(m_Material->GetContainer()->m_MatrixBuffer, 0);

			bufferNumber = 0;
			m_Renderer->GetDeviceContext()->VSSetConstantBuffers(bufferNumber, 1, &m_Material->GetContainer()->m_MatrixBuffer);

			m_Material->Bind();

			m_Renderer->GetDeviceContext()->DrawIndexed(m_Mesh->GetCount(), 0, 0);
		}
	}
}