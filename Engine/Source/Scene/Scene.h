#pragma once

#include <unordered_map>
#include <string>
#include <vector>

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

	class Scene
	{
	private:
		CCamera *m_Camera = nullptr;

		//The Name of the GameObject will be the key
		std::unordered_map<std::string, std::unique_ptr<GameObject>> m_GameObjects;

		//A collection of all object that can be rendered. The Renderer will get this list and uses this.
		std::unordered_map<GameObject*, CMeshRenderer*> m_Renderables;

	public:
		bool Initialize();
		void Update();
		void Shutdown();

		void AddRenderable(GameObject *a_Parent, CMeshRenderer *a_Renderable);
		void RemoveRenderable(GameObject *a_Parent);

		bool AddGameObject(std::unique_ptr<GameObject> a_ToAdd);
		void RemoveGameObject(std::string &a_Name);
		void ClearScene();

		void SetCamera(CCamera *a_Camera);
		CCamera* GetCamera();

		std::unordered_map<GameObject*, CMeshRenderer*> GetRenderables();
	};
}