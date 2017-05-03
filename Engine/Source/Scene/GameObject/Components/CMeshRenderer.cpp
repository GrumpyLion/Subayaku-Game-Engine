#include "CMeshRenderer.h"

#include "Graphics\Material.h"
#include "Graphics\Mesh.h"
#include "Core\Engine.h"
#include "Scene\Scene.h"
#include "Graphics\AssimpLoader.h"
#include "Graphics\Primitives.h"

namespace Scene
{
	bool CMeshRenderer::Initialize(GameObject *a_Parent, const char* a_ModelLocation, Graphics::Material *a_Material)
	{
		IComponent::Initialize(a_Parent);

		m_Mesh = new Graphics::Mesh();
		m_Mesh->HasIndices = true;
		m_Mesh->Mode = Graphics::EMeshPrimitive::TRIANGLES;
		//TODO MOVE THIS
		loadAssimp(a_ModelLocation, m_Mesh->Indices, m_Mesh->Vertices, m_Mesh->TexCoords, m_Mesh->Normals);

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
		delete m_Mesh;

		Core::Engine::StaticClass()->GetScene()->RemoveRenderable(Parent);
	}

	Graphics::Mesh *CMeshRenderer::GetMesh()
	{	return m_Mesh;	}

	Graphics::Material *CMeshRenderer::GetMaterial()
	{	return m_Material; 	}
}