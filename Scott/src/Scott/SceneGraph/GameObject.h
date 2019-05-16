#pragma once
#include <typeinfo>
#include <functional>


namespace Scott
{
	class BaseComponent;
	class TransformComponent;

	class GameObject
	{
	public:
		GameObject(const std::string& name);

		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void AddChild(GameObject* gameObject);
		void RemoveChild(GameObject* gameObject);

		void AddComponent(BaseComponent* component);
		void RemoveComponent(BaseComponent* component);

		TransformComponent* GetTransform() const { return m_pTransform; }

		GameObject* GetParent() const { return m_pParentObject; }

#pragma region 
		///This code is completely based on Overlord engine(GP2)
		template <class T>
		bool HasComponent(bool searchChildren = false)
		{
			return GetComponent<T>(searchChildren) != nullptr;
		}

		template <class T>
		T* GetComponent(bool searchChildren = false)
		{
			const type_info& ti = typeid(T);
			for (auto* component : m_Components)
			{
				if (component && typeid(*component) == ti)
					return static_cast<T*>(component);
			}

			if (searchChildren)
			{
				for (auto* child : m_Children)
				{
					if (child->GetComponent<T>(searchChildren) != nullptr)
						return child->GetComponent<T>(searchChildren);
				}
			}

			return nullptr;
		}

		template <class T>
		std::vector<T*> GetComponents(bool searchChildren = false)
		{
			const type_info& ti = typeid(T);
			std::vector<T*> components;

			for (auto* component : m_Components)
			{
				if (component && typeid(*component) == ti)
					components.push_back(static_cast<T*>(component));
			}

			if (searchChildren)
			{
				for (auto* child : m_Children)
				{
					auto childComponents = child->GetComponents<T>(searchChildren);

					for (auto* childComp : childComponents)
						components.push_back(static_cast<T*>(comp));
				}
			}

			return components;
		}

		template <class T>
		T* GetChild()
		{
			const type_info& ti = typeid(T);
			for (auto* child : m_Children)
			{
				if (child && typeid(*child) == ti)
					return static_cast<T*>(child);
			}
			return nullptr;
		}

		template <class T>
		std::vector<T*> GetChildren()
		{
			const type_info& ti = typeid(T);
			std::vector<T*> children;

			for (auto* child : m_Children)
			{
				if (child && typeid(*child) == ti)
					children.push_back((T*)child);
			}
			return children;
		}
#pragma endregion Template Methods

	protected:
		virtual void Initialize() {}
		virtual void Update() {}
		virtual void Render() {}

	private:
		friend class Scene;

		void RootUpdate();
		void RootRender();

		std::string m_Name;

		std::vector<GameObject*> m_Children;
		std::vector<BaseComponent*> m_Components;

		GameObject* m_pParentObject;
		TransformComponent* m_pTransform;
	};
}
