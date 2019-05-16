#include "scpch.h"
#include "BaseComponent.h"

#include "Scott/SceneGraph/GameObject.h"
#include "Scott/Components/TransformComponent.h"

namespace Scott
{
	BaseComponent::BaseComponent()
		: m_pGameObject{ nullptr }
	{

	}

	TransformComponent* BaseComponent::GetTransform() const
	{
		if (m_pGameObject == nullptr)
		{
			SC_CORE_ERROR("Failed to retrieve TransformComponent")
				return nullptr;
		}

		return m_pGameObject->GetTransform();
	}
}
