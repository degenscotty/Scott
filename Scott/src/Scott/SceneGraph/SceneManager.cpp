#include "scpch.h"
#include "Scott/SceneGraph/SceneManager.h"
#include "Scott/SceneGraph/Scene.h"

namespace Scott
{
	SceneManager::~SceneManager()
	{
		for (Scene* scene : m_Scenes)
			SafeDelete(scene);
	}

	void SceneManager::Update()
	{
		for (Scene* scene : m_Scenes)
		{
			scene->RootUpdate();
		}
	}

	void SceneManager::Render()
	{
		for (Scene* scene : m_Scenes)
		{
			scene->RootRender();
		}
	}

	Scene* SceneManager::GetScene(const std::string& sceneName)
	{
		std::vector<Scene*>::iterator it = std::find_if(m_Scenes.begin(), m_Scenes.end(), [&sceneName](Scene* scene) {
			if (scene->GetSceneName() == sceneName)
				return true;
			return false;
		});

		if (it == m_Scenes.end())
		{
			SC_CORE_ERROR("SceneManager::GetScene > Couldn't find requested scene in m_Scenes: {0}", sceneName);
			return nullptr;
		}

		return *it;
	}

	void SceneManager::CreateScene(const std::string& name)
	{
		m_Scenes.push_back(new Scene(name));
	}
}
