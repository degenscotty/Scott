#include "scpch.h"
#include "SpriteComponent.h"
#include "Scott/Helpers/ResourceManager.h"
#include "Scott/Components/TransformComponent.h"
#include "Scott/SceneGraph/GameObject.h"
#include "Scott/Renderer.h"

namespace Scott
{
	SpriteComponent::SpriteComponent(const std::string& file, int rows, int cols)
		: m_pTexture{ nullptr }
		, m_Pivot{}
		, m_Renderer(Renderer::GetInstance())
		, m_File{}
		, m_Rows{ rows }
		, m_Cols{ cols }
		, m_AnimTime{ 0.0f }
		, m_FramesPerSecond{ 6 }
		, m_ClipWidth{ 32 }
		, m_ClipHeight{ 32 }
		, m_AnimFrame{ 0 }
		, m_GameTime{ GameTime::GetInstance() }
		, m_ClipIndex{}
		, m_Clips{}
		, m_Flip{ SDL_RendererFlip::SDL_FLIP_NONE }
		, m_EndOfClip{ false }
	{
		SetTexture(file);
	}

	void SpriteComponent::SetTexture(const std::string& file)
	{
		if (file == m_File)
		{
			SC_CORE_INFO("SpriteComponent::SetTexture > This Texture has already been set! {0}", file);
		}

		m_File = file;
		m_pTexture = ResourceManager::GetInstance().LoadTexture(m_File);
	}

	void SpriteComponent::SetPivot(const glm::vec2& pivot)
	{
		m_Pivot = pivot;
	}

	void SpriteComponent::SetClipIndex(int index)
	{
		if (index > m_Clips.size() - 1)
		{
			SC_CORE_ERROR("SpriteComponent::SetClipIndex > This clip hasn't been added yet!");
			return;
		}

		m_ClipIndex = index;
		m_AnimFrame = m_ClipIndex * m_Cols;
		m_AnimTime = 0.0f;
	}

	void SpriteComponent::AddClip(int clipSize, bool repeat)
	{
		if (clipSize > m_Cols)
		{
			SC_CORE_ERROR("SpriteComponent::AddClip > ClipSize is too big for this spritesheet!");
			return;
		}

		m_Clips.push_back(std::make_pair(clipSize, repeat));
		m_EndedClips.push_back(false);
	}

	void SpriteComponent::SetFlip(const SDL_RendererFlip& flip)
	{
		m_Flip = flip;
	}

	void SpriteComponent::Update()
	{
		if (!m_EndedClips[m_ClipIndex])
		{
			m_AnimTime += m_GameTime.GetElapsedSec();

			if (m_AnimTime >= 1.0f / m_FramesPerSecond)
			{
				++m_AnimFrame;

				m_AnimTime = 0.0f;

				if (m_AnimFrame == m_ClipIndex * m_Cols + m_Clips[m_ClipIndex].first)
				{
					if (m_Clips[m_ClipIndex].second == true)
					{
						m_AnimFrame = m_ClipIndex * m_Cols;
					}
					else
					{
						m_AnimFrame = m_ClipIndex * m_Cols + m_Clips[m_ClipIndex].first - 1;
						m_EndedClips[m_ClipIndex] = true;
					}
				}
			}
		}
	}

	bool SpriteComponent::CheckEndOfCurrentClip()
	{
		return m_EndedClips[m_ClipIndex];
	}

	void SpriteComponent::Render()
	{
		if (!m_pTexture)
		{
			SC_CORE_ERROR("TextureComponent::Render > m_pTexture is nullptr!");
		}

		SDL_Rect src;
		src.x = (int)((m_AnimFrame % m_Cols) * m_ClipWidth);
		src.y = (int)((m_AnimFrame / m_Cols) * m_ClipHeight);
		src.w = (int)m_ClipWidth;
		src.h = (int)m_ClipHeight;

		TransformComponent* transformComponent = GetGameObject()->GetComponent<TransformComponent>();
		m_Renderer.RenderSpriteComponent(this, transformComponent, src, m_Flip);
	}
}

