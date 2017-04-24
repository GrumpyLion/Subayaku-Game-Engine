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

		m_Mesh = Graphics::Primitives::GetQuad();
		m_Material = new Graphics::Material();

		Graphics::TextureInfo texInfo;
		texInfo.UniformName = "uTexture";
		texInfo.Filter = Graphics::ETextureFilter::NEAREST;

		m_Material->AddTexture(a_TexturePath, texInfo);

		m_Material->FragmentShader = "Assets/Shaders/Sprite.fs";
		m_Material->VertexShader = "Assets/Shaders/Sprite.vs";

		Core::Engine::StaticClass()->GetScene()->AddRenderable(Parent, this);

		return true;
	}

	void CSprite::Update()
	{	}
}