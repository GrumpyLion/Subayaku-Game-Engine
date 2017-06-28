#include "Scene\GameObject\Components\CMeshRenderer.h"

#include "Scene\Scene.h"
#include "Graphics\Primitives.h"

namespace Scene
{
	CMeshRenderer::~CMeshRenderer()
	{
		Core::SEventDesc eventDesc{};

		eventDesc.Event = Core::EEvents::SCENE_MESHCOMPONENT_REMOVED;
		eventDesc.Description = &m_Entity;
		Core::EventHandler::StaticClass()->ForceEvent(eventDesc);
	}

	void CMeshRenderer::InitializeEntity()
	{	
		m_Entity.Mesh = m_Mesh;
		m_Entity.Material = &m_Material;
		m_Entity.Material->ParentTransform = Parent->Transform;
		m_Entity.Parent = Parent;
		m_Entity.MeshRenderer = this;

		Core::SEventDesc eventDesc{};
		eventDesc.Event = Core::EEvents::SCENE_MESHCOMPONENT_ADDED;
		eventDesc.Description = &m_Entity;
		Core::EventHandler::StaticClass()->AddEvent(eventDesc);
	}

	bool CMeshRenderer::Initialize(GameObject *a_Parent, std::string a_ModelLocation, Graphics::Material &a_Material)
	{
		IComponent::Initialize(a_Parent);
		
		m_Mesh.FilePath = a_ModelLocation;
		m_Mesh.HasIndices = true;
		m_Mesh.NeedsToBeLoaded = true;
		m_Mesh.ShouldCull = false;
		m_Mesh.Mode = Graphics::EMeshPrimitive::TRIANGLES;

		m_Material = a_Material;
		
		InitializeEntity();
		return true;
	}

	bool CMeshRenderer::Initialize(GameObject *a_Parent, Graphics::SMeshDesc &a_Desc, Graphics::Material &a_Material)
	{
		IComponent::Initialize(a_Parent);

		m_Mesh = a_Desc;
		m_Material = a_Material;
		
		InitializeEntity();
		return true;
	}

	void CMeshRenderer::Update()
	{
	}

	void CMeshRenderer::SetMaterial(Graphics::Material &a_Material)	{		m_Material = a_Material;	}

	Graphics::Material& CMeshRenderer::GetMaterial()	{		return m_Material;		}
}