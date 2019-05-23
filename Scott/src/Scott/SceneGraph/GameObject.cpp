#include "scpch.h"
#include "GameObject.h"

#include "Scott/Components/BaseComponent.h"
#include "Scott/Components/TransformComponent.h"

namespace Scott
{
	GameObject::GameObject(const std::string& name)
		: m_Name(name)
		, m_Components{}
		, m_Children{}
		, m_pParentObject(nullptr)
		, m_pTransform(nullptr)
	{
		m_pTransform = new TransformComponent();
		m_Components.push_back(m_pTransform);
	}

	GameObject::~GameObject()
	{
		for (BaseComponent* component : m_Components)
		{
			SafeDelete(component);
		}

		for (GameObject* child : m_Children)
		{
			SafeDelete(child);
		}
	}

	void GameObject::RootUpdate()
	{
		for (BaseComponent* component : m_Components)
		{
			component->Update();
		}

		for (GameObject* child : m_Children)
		{
			child->RootUpdate();
		}

		Update();
	}

	void GameObject::RootRender()
	{
		for (BaseComponent* component : m_Components)
		{
			component->Render();
		}

		for (GameObject* child : m_Children)
		{
			child->Render();
		}

		Render();
	}

	void GameObject::AddChild(GameObject* gameObject)
	{
		if (gameObject->m_pParentObject)
		{
			if (gameObject->m_pParentObject == this)
			{
				SC_CORE_ERROR("GameObject::AddChild > GameObject to add is already attached to this parent!");
			}
			else
			{
				SC_CORE_ERROR("GameObject::AddChild > GameObject to add is already attached to another GameObject!");
			}
			return;
		}

		gameObject->m_pParentObject = this;
		m_Children.push_back(gameObject);
	}

	void GameObject::RemoveChild(GameObject* gameObject)
	{
		auto it = find(m_Children.begin(), m_Children.end(), gameObject);

		if (it == m_Children.end())
		{
			SC_CORE_ERROR("GameObject::RemoveChild > GameObject to remove is not attached to this GameObject!");
			return;
		}
	}

	void GameObject::AddComponent(BaseComponent* component)
	{
		if (typeid(*component) == typeid(TransformComponent) && HasComponent<TransformComponent>())
		{
			SC_CORE_ERROR("GameObject::AddComponent > GameObject can contain only one TransformComponent!");
			return;
		}

		auto it = find(m_Components.begin(), m_Components.end(), component);

		if (it != m_Components.end())
		{
			SC_CORE_ERROR("GameObject::AddComponent > Component is already attached to this GameObject!");
			return;
		}


		m_Components.push_back(component);
		component->m_pGameObject = this;
	}

	void GameObject::RemoveComponent(BaseComponent* component)
	{
		auto it = find(m_Components.begin(), m_Components.end(), component);

		if (it == m_Components.end())
		{
			SC_CORE_ERROR("GameObject::RemoveComponent > Component is not attached to this GameObject!");
			return;
		}

		m_Components.erase(it);
		component->m_pGameObject = nullptr;
	}
}
