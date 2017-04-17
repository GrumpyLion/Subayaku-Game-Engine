#include "GLMaterial.h"
#include "GLShaderContainer.h"
#include "Utilities\Utilities.h"
#include "Graphics\Material.h"

namespace Graphics
{
	namespace OpenGL
	{
		GLMaterial::~GLMaterial()
		{
			SAFE_DELETE(m_Container);
		}

		bool GLMaterial::Initialize(Material *a_Material)
		{
			m_Container = new GLShaderContainer();

			if (!m_Container->Initialize(a_Material))
				return false;
			
			return true;
		}

		void GLMaterial::Bind()
		{
			m_Container->BindProgram();
		}
	}
}