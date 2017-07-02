#include "Scene\GameObject\Components\CMeshRenderer.h"

#include "Scene\Scene.h"
#include "Graphics\Primitives.h"

namespace Scene
{
	CMeshRenderer::~CMeshRenderer()
	{
		// Safety first
		//
		if (!m_Removed)
			Remove();
	}

	void CMeshRenderer::Remove()
	{
		Core::SEventDesc eventDesc{};
		eventDesc.Event = Core::EEvents::SCENE_MESHCOMPONENT_REMOVED;

		// Send an event to everything. The renderer will get this event and will delete the entity
		//
		eventDesc.Description = &m_Entity;
		Core::EventHandler::StaticClass()->ForceEvent(eventDesc);
		
		m_Removed = true;
	}

	void CMeshRenderer::InitializeEntity()
	{	
		m_Entity.Mesh = m_Mesh;
		m_Entity.Material = &m_Material;
		m_Entity.Parent = Parent;
		m_Entity.Transform = Parent->ModelTransform.get();
		m_Entity.MeshRenderer = this;

		Core::SEventDesc eventDesc{};
		eventDesc.Event = Core::EEvents::SCENE_MESHCOMPONENT_ADDED;
		eventDesc.Description = &m_Entity;
		Core::EventHandler::StaticClass()->AddEvent(eventDesc);
	}

	bool CMeshRenderer::Initialize(std::string a_ModelLocation, Graphics::Material &a_Material)
	{		
		// The model should have this attributes
		m_Mesh.FilePath = a_ModelLocation;
		m_Mesh.HasIndices = true;
		m_Mesh.NeedsToBeLoaded = true;
		m_Mesh.ShouldCull = true;
		m_Mesh.Mode = Graphics::EMeshPrimitive::TRIANGLES;

		m_Material = a_Material;
		
		InitializeEntity();
		return true;
	}

	bool CMeshRenderer::Initialize(Graphics::SMeshDesc &a_Desc, Graphics::Material &a_Material)
	{		
		m_Mesh = a_Desc;
		m_Material = a_Material;
		
		InitializeEntity();
		return true;
	}

	void CMeshRenderer::Update() {		}
}