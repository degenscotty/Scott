#pragma once
#include "SceneManager.h"

namespace Scott
{
	class GameObject;

	class Scene
	{
	public:
		Scene(const std::string& name);
		~Scene();

		void Add(GameObject* object);

		void Update();
		void Render() const;

		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		std::string m_Name{};
		std::vector<GameObject*> m_GameObjects;

		static unsigned int s_IdCounter; 
	};

}
