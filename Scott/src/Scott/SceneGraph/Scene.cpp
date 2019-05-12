#include "scpch.h"
#include "Scene.h"
#include "GameObject.h"

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

	void Scene::Update()
	{
		for (GameObject* gameObject : m_GameObjects)
		{
			gameObject->Update();
		}
	}

	void Scene::Render() const
	{
		for (GameObject* gameObject : m_GameObjects)
		{
			gameObject->Render();
		}
	}
}

