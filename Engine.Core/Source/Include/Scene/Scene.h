#pragma once

#include <unordered_map>
#include <string>
#include <vector>

#include "GameObject\GameObject.h"
#include "GameObject\Components\Transformation.h"
#include "GameObject\Components\CMeshRenderer.h"
#include "GameObject\Components\CCamera.h"
#include "GameObject\Components\CSprite.h"
#include "GameObject\Components\CScriptComponent.h"

#include "Utilities\Event\EventHandler.h"

#include <memory>

namespace Graphics
{
	class IRenderable;
}

namespace Scene
{
	class GameObject;
	class CCamera;
	class CMeshRenderer;
	class CLight;

	class Scene
	{
	private:
		CCamera *m_Camera = nullptr;
		CLight *m_DirectionalLight = nullptr;

		bool m_Clearing = false;
		// The Name of the GameObject will be the key
		std::unordered_map<std::string, std::unique_ptr<GameObject>> m_GameObjects;
		std::unordered_map<std::string, GameObject*> m_TickableGameObjects;

		// A collection of all object that can be rendered. The Renderer will get this list and uses this.
		std::unordered_map<GameObject*, CMeshRenderer*> m_Renderables;

		Callback m_Callback = nullptr;

	public:
		~Scene();
		Scene();

		bool Initialize();
		void Update();

		GameObject* InstantiateGameObject(std::string a_Name, bool a_IsTicking);

		// Instantiates an GameObject and returns an observable pointer
		//
		GameObject* InstantiateGameObject(std::string a_Name, Transformation& a_Transform, bool a_IsTicking);

		void AddRenderable(GameObject *a_Parent, CMeshRenderer *a_Renderable);
		void RemoveRenderable(GameObject *a_Parent);

		bool AddGameObject(std::unique_ptr<GameObject> a_ToAdd);
		void RemoveGameObject(std::string &a_Name);

		void ReloadForRendering();
		void ClearScene();

		void Listener(Core::SEventDesc &a_Desc);

		void SetCamera(CCamera *a_Camera);
		CCamera* GetCamera();

		std::unordered_map<GameObject*, CMeshRenderer*> GetRenderables();
	};
}