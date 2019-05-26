#include "scpch.h"
#include "Scene.h"

namespace Scott
{
	unsigned int Scene::s_IdCounter = 0;

	Scene::Scene(const std::string& name)
		: m_Name{ name }
		, m_GameObjects{}
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
		m_GameObjects.erase(std::remove_if(m_GameObjects.begin(), m_GameObjects.end(), [](GameObject* gameObject) {
			return gameObject->CheckDestroy();
		}), m_GameObjects.end());

		for (GameObject* gameObject : m_GameObjects)
		{
			gameObject->RootUpdate();

			if (gameObject->GetCollisionComponent())
			{
				m_CollisionComponents.push_back(gameObject->GetCollisionComponent());
			}
		}

		if (m_CollisionComponents.size() > 1)
		{
			for (int i{ 0 }; i != m_CollisionComponents.size() - 1; ++i)
			{
				for (int j{ i + 1 }; j < m_CollisionComponents.size(); ++j)
				{
					if (m_CollisionComponents[i]->IsColliding(m_CollisionComponents[j]->GetRect()))
					{
						GameObject* pGameObject = m_CollisionComponents[i]->GetGameObject();
						pGameObject->m_CollisionCallBack(*m_CollisionComponents[j]->GetGameObject());

						pGameObject = m_CollisionComponents[j]->GetGameObject();
						pGameObject->m_CollisionCallBack(*m_CollisionComponents[i]->GetGameObject());
					}
				}
			}
		}

		m_CollisionComponents.clear();
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


