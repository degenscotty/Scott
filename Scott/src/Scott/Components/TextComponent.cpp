#include "scpch.h"
#include "TextComponent.h"

#include "Scott/Renderer.h"
#include "Scott/Components/TransformComponent.h"
#include "Scott/Helpers/ResourceManager.h"
#include "Scott/SceneGraph/GameObject.h"

namespace Scott
{
	TextComponent::TextComponent(const std::string& file, const std::string& text, unsigned int size)
		: m_pFont(nullptr)
		, m_pTexture(nullptr)
		, m_UpdateText(true)
		, m_Text{ text }
		, m_Color{ 255, 255, 255 }
		, m_Renderer{ Renderer::GetInstance() }
		, m_FontData{}
	{
		SetFont(std::make_pair(file, size));
	}

	TextComponent::~TextComponent()
	{
		delete m_pFont;
		m_pFont = nullptr;
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	void TextComponent::SetText(const std::string& text)
	{
		m_Text = text;
		m_UpdateText = true;
	}

	void TextComponent::SetFont(const std::pair<std::string, unsigned int>& fontData)
	{
		if (fontData == m_FontData)
		{
			SC_CORE_INFO("TextComponent::SetFont > This Font has already been set! [{0}, {1}]", fontData.first, fontData.second);
			return;
		}

		m_FontData = fontData;
		m_pFont = ResourceManager::GetInstance().LoadFont(m_FontData);
	}

	void TextComponent::SetColor(const SDL_Color& color)
	{
		m_Color = color;
	}

	void TextComponent::SetPivot(const glm::vec3& pivot)
	{
		m_pPivot = pivot;
	}

	void TextComponent::Update()
	{
		if (!m_UpdateText) return;

		if (!m_pFont)
		{
			SC_CORE_ERROR("TextComponent::Update() > Rendering Text failed: m_pFont was nullptr");
		}

		SDL_Surface* pSurface = TTF_RenderText_Blended(m_pFont->GetTTFFont(), m_Text.c_str(), m_Color);

		if (pSurface == nullptr)
		{
			SC_CORE_ERROR("TextComponent::Update() > Rendering Text failed, Surface invalid: {0}", SDL_GetError());
		}

		SDL_Texture* pTexture = SDL_CreateTextureFromSurface(m_Renderer.GetSDLRenderer(), pSurface);

		if (pTexture == nullptr)
		{
			SC_CORE_ERROR("TextComponent::Update() > Creating Text Texture from Surface, Texture Invalid: {0}", SDL_GetError());
		}

		SDL_FreeSurface(pSurface);

		delete m_pTexture;
		m_pTexture = new Texture2D(pTexture);
	}

	void TextComponent::Render()
	{
		if (m_pTexture)
		{
			TransformComponent* transformComponent = GetGameObject()->GetComponent<TransformComponent>();
			Renderer::GetInstance().RenderTextComponent(this, transformComponent);		
		}
	}
}
