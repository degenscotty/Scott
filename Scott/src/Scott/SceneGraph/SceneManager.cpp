#include "scpch.h"
#include "SceneManager.h"
#include "Scene.h"

namespace Scott
{
	SceneManager* SceneManager::s_Instance = new SceneManager();

	SceneManager::~SceneManager()
	{
		for (Scene* scene : m_Scenes)
			SafeDelete(scene);
	}

	void SceneManager::Update()
	{
		for (Scene* scene : m_Scenes)
		{
			scene->Update();
		}
	}

	void SceneManager::Render()
	{
		for (Scene* scene : m_Scenes)
		{
			scene->Render();
		}
	}

	void SceneManager::CreateScene(const std::string& name)
	{
		m_Scenes.push_back(new Scene(name));
	}
}
