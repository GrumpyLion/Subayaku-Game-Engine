#include "DirectX\D3DEntity.h"

#include "DirectX\D3DRenderer.h"
#include "DirectX\D3DMesh.h"

#include "Scene\GameObject\GameObject.h"
#include "Scene\GameObject\Components\CMeshRenderer.h"

namespace Graphics
{
	namespace DirectX
	{
		bool D3DEntity::Initialize(SEntityDesc &a_Desc, IRenderer *a_Renderer)
		{
			m_Renderer = static_cast<D3DRenderer*>(a_Renderer);

			if (CheckIfPointerIsInvalid(m_Renderer))
				return false;

			m_Material = std::make_unique<D3DMaterial>();

			if (!m_Material->Initialize(a_Desc.Material, a_Renderer))
				return false;

			m_Mesh = static_cast<D3DMesh*>(m_Renderer->GetCache()->LoadMesh(a_Desc.Mesh));
			if (CheckIfPointerIsInvalid(m_Mesh))
				return false;

			if (CheckIfPointerIsInvalid(m_Renderer))
				return false;

			return true;
		}

		void D3DEntity::AddInstance(Scene::CMeshRenderer *a_MeshRenderer)
		{

		}

		void D3DEntity::RemoveInstance(Scene::CMeshRenderer *a_MeshRenderer)
		{

		}

		void D3DEntity::Render()
		{
			m_Mesh->Bind();

			m_Material->Bind();

			if (HasIndices)
				m_Renderer->GetDeviceContext()->DrawIndexed(m_Mesh->GetCount(), 0, 0);
			else
				m_Renderer->GetDeviceContext()->Draw(m_Mesh->GetCount(), 0);
		}
	}
}