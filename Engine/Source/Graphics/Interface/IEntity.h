#pragma once

#include "Graphics\Cache\SMeshDesc.h"
#include "Graphics\Material.h"
#include "Scene\GameObject\GameObject.h"

namespace Graphics
{
	class IEntity
	{
	public:
		virtual ~IEntity() { }
		virtual	bool Initialize(SMeshDesc &a_Mesh, Material *a_Material, Scene::GameObject *a_Parent) = 0;
		virtual void Render() = 0;
	};
}