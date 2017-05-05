#include "CMeshRenderer.h"

#include "Graphics\Material.h"
#include "Core\Engine.h"
#include "Scene\Scene.h"
#include "Graphics\Primitives.h"

namespace Scene
{
	bool CMeshRenderer::Initialize(GameObject *a_Parent, const char* a_ModelLocation, Graphics::Material *a_Material)
	{
		IComponent::Initialize(a_Parent);

		//Graphics::Primitives::GetQuad(m_Mesh);
		m_Mesh.FilePath = "Assets/Models/sphere.obj";
		m_Mesh.HasIndices = true;
		m_Mesh.ShouldCull = false;
		m_Mesh.Mode = Graphics::EMeshPrimitive::TRIANGLES;
		
		m_Material = a_Material;
		
		Core::Engine::StaticClass()->GetScene()->AddRenderable(Parent, this);
		return true;
	}

	void CMeshRenderer::Update()
	{
	}

	void CMeshRenderer::Shutdown()
	{
		delete m_Material;
		Core::Engine::StaticClass()->GetScene()->RemoveRenderable(Parent);
	}

	Graphics::SMeshDesc &CMeshRenderer::GetMesh()
	{	return m_Mesh;	}

	Graphics::Material *CMeshRenderer::GetMaterial()
	{	return m_Material; 	}
}