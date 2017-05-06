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
			SafeDelete(m_Material);
			//SAFE_DELETE(m_Mesh);
		}

		bool D3DEntity::Initialize(SMeshDesc &a_Mesh, Material *a_Material, Scene::GameObject *a_Parent)
		{
			m_Parent = a_Parent;
			m_Renderer = dynamic_cast<D3DRenderer*>(Core::Engine::StaticClass()->GetRenderer());

			if (CheckIfPointerIsValid(m_Renderer))
				return false;

			m_Material = new D3DMaterial();
			if (!m_Material->Initialize(a_Material))
				return false;

			m_Mesh = dynamic_cast<D3DMesh*>(Core::Engine::StaticClass()->GetCache()->LoadMesh(a_Mesh));

			if (CheckIfPointerIsValid(m_Renderer))
				return false;

			return true;
		}

		void D3DEntity::Render()
		{
			m_Mesh->Bind();

			m_Material->Bind(m_Parent);

			m_Renderer->GetDeviceContext()->DrawIndexed(m_Mesh->GetCount(), 0, 0);
		}
	}
}