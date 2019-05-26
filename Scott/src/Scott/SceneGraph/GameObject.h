#pragma once
#include <typeinfo>
#include <functional>

#define BIND_COLLISION_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace Scott
{
	class BaseComponent;
	class TransformComponent;
	class CollisionComponent;

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

		void SetCollisionCallBack(const std::function<void(GameObject&)>& collisionCallBack) { m_CollisionCallBack = collisionCallBack; }

		TransformComponent* GetTransform() const { return m_pTransform; }
		CollisionComponent* GetCollisionComponent() const { return m_pCollisionComponent; }

		GameObject* GetParent() const { return m_pParentObject; }

		void Destroy() { m_Destroy = true; }
		bool CheckDestroy() { return m_Destroy; }

		const std::string& GetName() { return m_Name; }

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

#pragma endregion Template Methods

	protected:
		//virtual void Initialize() {}
		virtual void Update() {}
		virtual void Render() {}

	private:
		friend class Scene;

		void RootUpdate();
		void RootRender();

		std::string m_Name;
		bool m_Destroy;

		std::vector<GameObject*> m_Children;
		std::vector<BaseComponent*> m_Components;

		GameObject* m_pParentObject;
		TransformComponent* m_pTransform;
		CollisionComponent* m_pCollisionComponent;

		std::function<void(GameObject&)> m_CollisionCallBack;
	};
}
