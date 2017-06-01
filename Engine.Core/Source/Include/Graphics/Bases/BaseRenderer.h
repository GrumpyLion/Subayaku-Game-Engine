#pragma once

#include "Graphics\Interfaces\IRenderer.h"
#include "Utilities\GraphicsCache.h"
#include "Graphics\RenderFactory.h"

namespace Graphics
{
	template <typename TEntity, typename TTexture, typename TMesh, typename TShader, typename TShaderBuffer>
	class BaseRenderer : public IRenderer
	{
	protected:
		Core::Engine *m_Engine = nullptr;
		Scene::CCamera *m_Camera = nullptr;

		std::unordered_map<Scene::CMeshRenderer*, std::unique_ptr<TEntity>> m_Entities;

		std::unique_ptr<RenderFactory<TTexture, TMesh, TShader, TShaderBuffer>> m_RenderFactory;

		std::unique_ptr<Core::GraphicsCache<TTexture, TMesh, TShader, TShaderBuffer>> m_Cache;

	public:
		void SetEngine(Core::Engine *a_Engine) override
		{
			m_Engine = a_Engine;

			m_RenderFactory = std::make_unique<RenderFactory<TTexture, TMesh, TShader, TShaderBuffer>>();

			m_Cache = std::make_unique<Core::GraphicsCache<TTexture, TMesh, TShader, TShaderBuffer>>();
			m_Cache->Initialize(m_RenderFactory.get(), this);
		}

		Core::Engine *GetEngine() override
		{
			return m_Engine;
		}

		Core::GraphicsCache<TTexture, TMesh, TShader, TShaderBuffer>* GetCache()
		{
			return m_Cache.get();
		}

		void AddRenderable(SEntityDesc &a_Desc, Scene::CMeshRenderer *a_MeshRenderer) override
		{
			if (a_MeshRenderer == nullptr)
				return;

			if (m_Entities.find(a_MeshRenderer) != m_Entities.end())
			{
				LogErr("CMeshrenderer is already added\n");
				return;
			}

			auto temp = std::make_unique<TEntity>();

			if (!temp->Initialize(a_Desc, this))
			{
				LogErr("Error while trying to add a new Renderable\n");
				return;
			}

			m_Entities.insert({ a_MeshRenderer, std::move(temp) });
		}

		void RemoveRenderable(Scene::CMeshRenderer *a_MeshRenderer) override
		{
			if (a_MeshRenderer == nullptr)
				return;

			if (m_Entities.find(a_MeshRenderer) == m_Entities.end())
			{
				LogErr("CMeshrenderer was not found\n");
				return;
			}
			else
			{
				m_Entities.erase(a_MeshRenderer);
			}
		}

		void SetCamera(Scene::CCamera *a_Camera)override
		{
			m_Camera = a_Camera;
		}

		Scene::CCamera* GetCamera() override
		{
			return m_Camera;
		}
	};
}