#include "CMeshRenderer.h"

#include "Core\Engine.h"
#include "Scene\Scene.h"
#include "Graphics\Primitives.h"

namespace Scene
{
	CMeshRenderer::~CMeshRenderer()
	{
		Core::Engine::StaticClass()->GetScene()->RemoveRenderable(Parent);
	}

	bool CMeshRenderer::Initialize(GameObject *a_Parent, const char* a_ModelLocation, std::unique_ptr<Graphics::Material> a_Material)
	{
		IComponent::Initialize(a_Parent);

		//Graphics::Primitives::GetQuad(m_Mesh);
		m_Mesh.FilePath = a_ModelLocation;
		m_Mesh.HasIndices = true;
		m_Mesh.ShouldCull = false;
		m_Mesh.Mode = Graphics::EMeshPrimitive::TRIANGLES;
		
		m_Material = std::move(a_Material);
		
		Core::Engine::StaticClass()->GetScene()->AddRenderable(Parent, this);
		return true;
	}

	bool CMeshRenderer::Initialize(GameObject *a_Parent, Graphics::SMeshDesc &a_Desc, std::unique_ptr<Graphics::Material> a_Material)
	{
		IComponent::Initialize(a_Parent);
		m_Mesh = a_Desc;
		m_Material = std::move(a_Material);

		Core::Engine::StaticClass()->GetScene()->AddRenderable(Parent, this);
		return true;
	}

	void CMeshRenderer::Update()
	{
	}

	Graphics::SMeshDesc &CMeshRenderer::GetMesh()
	{	return m_Mesh;	}

	Graphics::Material *CMeshRenderer::GetMaterial()
	{	return m_Material.get(); 	}
}