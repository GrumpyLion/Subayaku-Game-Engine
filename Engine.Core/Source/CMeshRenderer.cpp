#include "Scene\GameObject\Components\CMeshRenderer.h"

#include "Core\Engine.h"
#include "Scene\Scene.h"
#include "Graphics\Primitives.h"

#include "OpenGL\GLMaterial.h"
#include "DirectX\D3DMaterial.h"

#include "Graphics\Interfaces\IRenderer.h"

#include "Graphics\Loaders\AssimpLoader.h"

#include "Graphics\Descriptions\SEntityDesc.h"

namespace Scene
{
	CMeshRenderer::~CMeshRenderer()
	{
		Core::Engine::StaticClass()->GetScene()->RemoveRenderable(Parent);
	}

	void CMeshRenderer::InitializeEntity()
	{
		Graphics::SEntityDesc entity{};
	
		//Load the mesh from cache..
		if (m_Mesh.Vertices.size() == 0)
			LoadAssimpObj(m_Mesh);

		entity.Mesh = m_Mesh;
		entity.Material = m_Material.get();
		entity.Material->ParentTransform = Parent->Transform;

		Core::Engine::StaticClass()->GetRenderer()->AddRenderable(entity, this);
	}

	bool CMeshRenderer::Initialize(GameObject *a_Parent, const char* a_ModelLocation, std::unique_ptr<Graphics::Material> a_Material)
	{
		IComponent::Initialize(a_Parent);
		
		m_Mesh.FilePath = a_ModelLocation;
		m_Mesh.HasIndices = true;
		m_Mesh.ShouldCull = false;
		m_Mesh.Mode = Graphics::EMeshPrimitive::TRIANGLES;

		m_Material = std::move(a_Material);
		
		InitializeEntity();

		Core::Engine::StaticClass()->GetScene()->AddRenderable(Parent, this);
		return true;
	}

	bool CMeshRenderer::Initialize(GameObject *a_Parent, Graphics::SMeshDesc &a_Desc, std::unique_ptr<Graphics::Material> a_Material)
	{
		IComponent::Initialize(a_Parent);

		m_Mesh = a_Desc;
		m_Material = std::move(a_Material);
		
		InitializeEntity();

		Core::Engine::StaticClass()->GetScene()->AddRenderable(Parent, this);
		return true;
	}

	void CMeshRenderer::Update()
	{

	}
}