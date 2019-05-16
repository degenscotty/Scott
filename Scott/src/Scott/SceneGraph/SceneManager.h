#pragma once
#include "Scott/Helpers/Singleton.h"

namespace Scott
{
	class Scene;

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void CreateScene(const std::string& name);

		~SceneManager();

		void Update();
		void Render();
		Scene* GetScene(const std::string& sceneName);

	private:
		std::vector<Scene*> m_Scenes;
	};

}
