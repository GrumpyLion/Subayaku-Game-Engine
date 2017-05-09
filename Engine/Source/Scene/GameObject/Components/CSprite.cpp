#include "CSprite.h"
#include "Graphics\Material.h"
#include "Graphics\Primitives.h"
#include "Core\Engine.h"
#include "Scene\Scene.h"

namespace Scene
{
	bool CSprite::Initialize(GameObject *a_Parent, const char* a_TexturePath)
	{
		IComponent::Initialize(a_Parent);

		Graphics::Primitives::GetQuad(m_Mesh);
		m_Mesh.ShouldCull = false;
		m_Mesh.HasIndices = true;
		m_Mesh.Mode = Graphics::EMeshPrimitive::TRIANGLES;
		m_Material = std::make_unique<Graphics::Material>();

		Graphics::STextureDesc texInfo;
		texInfo.UniformName = "uTexture";
		texInfo.Filter = Graphics::ETextureFilter::NEAREST;
		texInfo.FilePath = a_TexturePath;
		
		//insert cache
		m_Material->AddTexture(texInfo);

		m_Material->Shaders.ShaderContainerName = "Sprite";
		m_Material->Shaders.FragmentShaderPath = "Sprite.fs";
		m_Material->Shaders.VertexShaderPath = "Sprite.vs";

		Core::Engine::StaticClass()->GetScene()->AddRenderable(Parent, this);

		return true;
	}

	void CSprite::Update()
	{	}
}