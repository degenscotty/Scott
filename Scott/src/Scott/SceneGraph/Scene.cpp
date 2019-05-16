#include "scpch.h"
#include "Scene.h"

namespace Scott
{
	unsigned int Scene::s_IdCounter = 0;

	Scene::Scene(const std::string& name)
		: m_Name{ name }
	{

	}

	Scene::~Scene()
	{
		for (GameObject* gameObject : m_GameObjects)
		{
			SafeDelete(gameObject);
		}
	}

	void Scene::Add(GameObject* object)
	{
		m_GameObjects.push_back(object);
	}

	void Scene::RootUpdate()
	{
		for (GameObject* gameObject : m_GameObjects)
		{
			gameObject->RootUpdate();
		}
	}

	void Scene::RootRender()
	{
		for (GameObject* gameObject : m_GameObjects)
		{
			gameObject->RootRender();
		}
	}

	const std::string& Scene::GetSceneName()
	{
		return m_Name;
	}
}


