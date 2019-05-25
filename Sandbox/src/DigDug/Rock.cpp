#include "scpch.h"
#include "Rock.h"

namespace Scott
{
	Rock::Rock(const glm::vec2& position)
		: GameObject{ "Rock" }
		, m_State{ State::Idle }
		, m_pTransform{ GetComponent<TransformComponent>() }
		, m_pSpriteComponent{ nullptr }
		, m_LevelManager{ LevelManager::GetInstance() }
		, m_GameTime{ GameTime::GetInstance() }
		, m_MoveSpeed{ 30.0f }
		, m_ClipIndex{}
	{
		AddComponent(new SpriteComponent("Rock.png", 1, 4));
		m_pSpriteComponent = GetComponent<SpriteComponent>();
		m_pSpriteComponent->AddClip(4, false);
		m_pSpriteComponent->AddClip(1, false);
		SetClipIndex(1);

		m_pTransform->TranslateWorld(position);
		m_Destination = m_pTransform->GetWorldPosition();
	}

	Rock::~Rock()
	{
		m_pSpriteComponent = nullptr;
		m_pTransform = nullptr;
	}

	void Rock::Update()
	{
		glm::vec2 currentPosition = m_pTransform->GetWorldPosition();

		m_GridPosX = (int)currentPosition.x / 32;
		m_GridPosY = (int)currentPosition.y / 32;

		if (m_LevelManager.GetTile(m_GridPosX, m_GridPosY + 1) == '#' && m_State == State::Idle)
		{
			m_Destination.y += 32.0f;
			m_State = State::Falling;
		}

		switch (m_State)
		{
		case State::Idle:
		{
		}
		break;
		case State::Falling:
		{
			if (m_pTransform->GetWorldPosition().y + (m_MoveSpeed * m_GameTime.GetElapsedSec()) > m_Destination.y)
			{
				if (m_LevelManager.GetTile(m_GridPosX, m_GridPosY + 2) == '.' && m_State == State::Falling)
				{
					m_pTransform->TranslateWorld(m_Destination);
					m_State = State::Braking;
				}
				else
				{
					m_Destination.y += 32.0f;
				}
			}
			else
			{
				m_pTransform->MoveWorld(0, +(m_MoveSpeed * m_GameTime.GetElapsedSec()));
			}
		}
		break;
		case State::Braking:
		{
			SetClipIndex(0);
			if (m_pSpriteComponent->CheckEndOfCurrentClip())
			{
				Destroy();
			}
		}
		break;
		}
	}

	void Rock::SetClipIndex(int index)
	{
		if (m_ClipIndex != index)
		{
			m_ClipIndex = index;
			m_pSpriteComponent->SetClipIndex(index);
		}
	}
}
