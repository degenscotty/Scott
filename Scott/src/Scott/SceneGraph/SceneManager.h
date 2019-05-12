#pragma once

namespace Scott
{
	class Scene;

	class SceneManager final
	{
	public:
		void CreateScene(const std::string& name);

		~SceneManager();

		void Update();
		void Render();

		inline static SceneManager* get() { return s_Instance; }

	private:
		std::vector<Scene*> m_Scenes;

		static SceneManager* s_Instance;
	};

}
