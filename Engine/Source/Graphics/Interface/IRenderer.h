#pragma once

#include "SRendererDesc.h"
#include "Scene\GameObject\Components\CMeshRenderer.h"
#include "Scene\GameObject\Components\CCamera.h"

namespace Graphics
{
	class IRenderer
	{
	public:
		virtual ~IRenderer() {}

		virtual bool Initialize(SRendererDesc &a_Desc) = 0;
		virtual void Render() = 0;
		virtual void AddRenderable(Scene::CMeshRenderer *a_MeshRenderer) = 0;
		virtual void RemoveRenderable(Scene::CMeshRenderer *a_MeshRenderer) = 0;
		virtual void SetCamera(Scene::CCamera *a_Camera) = 0;
		virtual Scene::CCamera *GetCamera() = 0;
	};
}