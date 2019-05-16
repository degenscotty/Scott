#include "scpch.h"
#include "TextureComponent.h"
#include "Scott/Helpers/ResourceManager.h"
#include "Scott/Components/TransformComponent.h"
#include "Scott/SceneGraph/GameObject.h"
#include "Scott/Renderer.h"

namespace Scott
{
	TextureComponent::TextureComponent()
		: m_pTexture{ nullptr }
		, m_Pivot{}
		, m_Renderer(Renderer::GetInstance())
	{
	}

	void TextureComponent::Render()
	{
		if (m_pTexture)
		{
			TransformComponent* component = GetGameObject()->GetComponent<TransformComponent>();
			m_Renderer.RenderTextureComponent(this, component);
		}
	}

	void TextureComponent::SetPivot(const glm::vec2& pivot)
	{
		m_Pivot = pivot;
	}

	void TextureComponent::SetTexture(const std::string& file)
	{
		m_pTexture = ResourceManager::GetInstance().LoadTexture(file);
	}

}
