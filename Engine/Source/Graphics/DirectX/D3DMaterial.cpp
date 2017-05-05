#include "D3DMaterial.h"

namespace Graphics
{
	namespace DirectX
	{
		D3DMaterial::~D3DMaterial()
		{
			delete m_Container;
		}

		bool D3DMaterial::Initialize(Material *a_Material)
		{
			m_Container = new D3DShaderContainer();
			m_Container->Initialize(a_Material);

			return true;
		}

		void D3DMaterial::Bind()
		{
			m_Container->BindProgram();
		}

		D3DShaderContainer *D3DMaterial::GetContainer()
		{
			return m_Container;
		}
	}
}