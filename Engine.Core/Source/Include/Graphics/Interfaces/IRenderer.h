#pragma once

#include "Graphics\Descriptions\SRendererDesc.h"
#include "Graphics\Descriptions\SEntityDesc.h"
#include "Graphics\Enums\ShaderStages.h"

#include "Core\Engine.h"
#include "Utilities\Event\EventHandler.h"
#include "Graphics\Camera.h"

namespace Graphics
{
	class IRenderer
	{
	public:
		virtual ~IRenderer() {}

		virtual bool Initialize(SRendererDesc &a_Desc) = 0;
		virtual void Render() = 0;		

		virtual void AddRenderable(SEntityDesc &a_Desc) = 0;
		virtual void RemoveRenderable(SEntityDesc &a_Desc) = 0;

		virtual Camera *GetCamera() = 0;
		virtual Core::Engine *GetEngine() = 0;

		virtual void EventListener(Core::SEventDesc &a_Desc) = 0;
		
		virtual EShaderStage GetShaderStage() = 0;
	};
}