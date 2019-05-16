#pragma once
#include "SceneManager.h"

#include "Scott/SceneGraph/GameObject.h"

namespace Scott
{
	class Scene
	{
	public:
		Scene(const std::string& name);
		~Scene();

		void Add(GameObject* object);

		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		const std::string& GetSceneName();

	protected:
		virtual void Initialize() {}
		virtual void Update() {}
		virtual void Render() {}

	private:
		friend class SceneManager;

		void RootUpdate();
		void RootRender();

		std::string m_Name{};
		std::vector<GameObject*> m_GameObjects;

		static unsigned int s_IdCounter; 
	};

}
