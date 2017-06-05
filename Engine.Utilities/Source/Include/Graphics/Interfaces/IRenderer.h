#pragma once

#include "Graphics\Descriptions\SRendererDesc.h"
#include "Graphics\Descriptions\SEntityDesc.h"

#include "Core\Engine.h"
#include "Utilities\Event\EventHandler.h"
#include "Scene\GameObject\Components\CCamera.h"

namespace Graphics
{
	class IRenderer
	{
	public:
		virtual ~IRenderer() {}

		virtual bool Initialize(SRendererDesc &a_Desc) = 0;
		virtual void Render() = 0;		

		virtual void AddRenderable(SEntityDesc &a_Desc) = 0;
		virtual void RemoveRenderable(Scene::CMeshRenderer *a_MeshRenderer) = 0;

		virtual Scene::CCamera *GetCamera() = 0;
		virtual Core::Engine *GetEngine() = 0;

		virtual void EventListener(Core::SEventDesc &a_Desc) = 0;
	};
}