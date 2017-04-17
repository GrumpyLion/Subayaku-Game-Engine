#pragma once

#include <unordered_map>
#include <string>
#include <vector>

namespace Graphics
{
	class IRenderable;
}

namespace Scene
{
	class GameObject;
	class CMeshRenderer;

	class Scene
	{
	private:
		//The Name of the GameObject will be the key
		std::unordered_map<std::string, GameObject*> m_GameObjects{};

		//A collection of all object that can be rendered. The Renderer will get this list and uses this.
		std::unordered_map<GameObject*, CMeshRenderer*> m_Renderarbles{};

	public:
		bool Initialize();
		void Update();
		void Shutdown();

		void AddRenderable(GameObject *a_Parent, CMeshRenderer *a_Renderable);
		void RemoveRenderable(GameObject *a_Parent);

		bool AddGameObject(GameObject *a_ToAdd);
		void RemoveGameObject(std::string &a_Name);
		void ClearScene();

		std::unordered_map<GameObject*, CMeshRenderer*> GetRenderables();
	};
}