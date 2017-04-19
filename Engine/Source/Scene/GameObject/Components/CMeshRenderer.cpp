#include "CMeshRenderer.h"

#include "Graphics\Material.h"
#include "Graphics\Mesh.h"
#include "Core\Engine.h"
#include "Scene\Scene.h"
#include "Graphics\AssimpLoader.h"

namespace Scene
{
	bool CMeshRenderer::Initialize(GameObject *a_Parent)
	{
		IComponent::Initialize(a_Parent);

		m_Mesh = new Graphics::Mesh();
		//TODO MOVE THIS
		loadAssimp("teapot.obj", m_Mesh->Indices, m_Mesh->Vertices, m_Mesh->TexCoords, m_Mesh->Normals);

		m_Material = new Graphics::Material();

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