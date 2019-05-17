#include "scpch.h"
#include "TextureComponent.h"
#include "Scott/Helpers/ResourceManager.h"
#include "Scott/Components/TransformComponent.h"
#include "Scott/SceneGraph/GameObject.h"
#include "Scott/Renderer.h"

namespace Scott
{
	TextureComponent::TextureComponent(const std::string& file)
		: m_pTexture{ nullptr }
		, m_Pivot{}
		, m_Renderer(Renderer::GetInstance())
		, m_File{}
	{
		SetTexture(file);
	}

	void TextureComponent::SetTexture(const std::string& file)
	{
		if (file == m_File)
		{
			SC_CORE_INFO("TextureComponent::SetTexture > This Texture has already been set! {0}", file);
		}

		m_File = file;
		m_pTexture = ResourceManager::GetInstance().LoadTexture(m_File);
	}

	void TextureComponent::SetPivot(const glm::vec2& pivot)
	{
		m_Pivot = pivot;
	}

	void TextureComponent::Render()
	{
		if (!m_pTexture)
		{
			SC_CORE_ERROR("TextureComponent::Render > Failed to render Texture!");
		}

		TransformComponent* transformComponent = GetGameObject()->GetComponent<TransformComponent>();
		m_Renderer.RenderTextureComponent(this, transformComponent);
	}
}
