#include "Scene\GameObject\Components\CMeshRenderer.h"

#include "Scene\Scene.h"
#include "Graphics\Primitives.h"

#include "Graphics\Loaders\AssimpLoader.h"

namespace Scene
{
	CMeshRenderer::~CMeshRenderer()
	{
		Core::SEventDesc eventDesc{};

		eventDesc.Event = Core::EEvents::SCENE_MESHCOMPONENT_REMOVED;
		eventDesc.Description = m_Entity.get();
		Core::EventHandler::StaticClass()->AddEvent(eventDesc);
	}

	void CMeshRenderer::InitializeEntity()
	{
		m_Entity = std::make_unique<Graphics::SEntityDesc>();
	
		//Load the mesh from cache..
		if (m_Mesh.Vertices.size() == 0)
			LoadAssimpObj(m_Mesh);

		m_Entity->Mesh = m_Mesh;
		m_Entity->MeshRenderer = this;
		m_Entity->Material = m_Material.get();
		m_Entity->Material->ParentTransform = Parent->Transform;
		m_Entity->Parent = Parent;

		Core::SEventDesc eventDesc{};
		eventDesc.Event = Core::EEvents::SCENE_MESHCOMPONENT_ADDED;
		eventDesc.Description = m_Entity.get();
		Core::EventHandler::StaticClass()->AddEvent(eventDesc);
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
		return true;
	}

	bool CMeshRenderer::Initialize(GameObject *a_Parent, Graphics::SMeshDesc &a_Desc, std::unique_ptr<Graphics::Material> a_Material)
	{
		IComponent::Initialize(a_Parent);

		m_Mesh = a_Desc;
		m_Material = std::move(a_Material);
		
		InitializeEntity();
		return true;
	}

	void CMeshRenderer::Update()
	{

	}
}