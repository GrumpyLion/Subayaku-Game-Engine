#include "CMeshRenderer.h"

#include "Graphics\Material.h"
#include "Graphics\Mesh.h"
#include "Core\Engine.h"
#include "Scene\Scene.h"

namespace Scene
{
	bool CMeshRenderer::Initialize(GameObject *a_Parent)
	{
		IComponent::Initialize(a_Parent);

		//TODO load from file

		m_Mesh = new Graphics::Mesh();
		m_Material = new Graphics::Material();

		m_Mesh->Vertices.push_back(-0.5f);
		m_Mesh->Vertices.push_back(-0.5f);
		m_Mesh->Vertices.push_back(0);

		m_Mesh->Vertices.push_back(0.5f);
		m_Mesh->Vertices.push_back(-0.5f);
		m_Mesh->Vertices.push_back(0);

		m_Mesh->Vertices.push_back(0.5f);
		m_Mesh->Vertices.push_back(0.5f);
		m_Mesh->Vertices.push_back(0);

		m_Mesh->Vertices.push_back(-0.5f);
		m_Mesh->Vertices.push_back(0.5f);
		m_Mesh->Vertices.push_back(0);

		m_Mesh->Indices.push_back(0);
		m_Mesh->Indices.push_back(1);
		m_Mesh->Indices.push_back(2);

		m_Mesh->Indices.push_back(0);
		m_Mesh->Indices.push_back(2);
		m_Mesh->Indices.push_back(3);

		m_Material->FragmentShader = "Test.frag";
		m_Material->VertexShader = "Test.vert";

		Core::Engine::StaticClass()->GetScene()->AddRenderable(Parent, this);

		return true;
	}

	void CMeshRenderer::Update()
	{

	}

	void CMeshRenderer::Shutdown()
	{
		Core::Engine::StaticClass()->GetScene()->RemoveRenderable(Parent);
	}

	Graphics::Mesh *CMeshRenderer::GetMesh()
	{	return m_Mesh;	}

	Graphics::Material *CMeshRenderer::GetMaterial()
	{	return m_Material; 	}
}