#include "scpch.h"
#include "Player.h"
#include "Scott/Input.h"
#include "Scott/InputDefinitions.h"
#include "Scott/Components/Components.h"

namespace Scott
{
	Player::Player()
		: GameObject{ "Player" }
		, m_State{ State::Idle }
		, m_Direction{ Direction::Right }
		, m_MoveSpeed{ 60.0f }
		, m_pTransform{ GetComponent<TransformComponent>() }
		, m_pSpriteComponent{ nullptr }
		, m_GameTime{ GameTime::GetInstance() }
		, m_LevelManager{ LevelManager::GetInstance() }
		, m_Flip{ SDL_RendererFlip::SDL_FLIP_NONE }
		, m_GridPosX{}
		, m_GridPosY{}
		, m_ClipIndex{}
	{
		AddComponent(new SpriteComponent("SpriteSheet.png", 2, 2));
		m_pSpriteComponent = GetComponent<SpriteComponent>();
		m_pSpriteComponent->AddClip(2, true);
		m_pSpriteComponent->AddClip(2, true);
		m_pSpriteComponent->AddClip(1, false);
		SetClipIndex(2);

		m_pTransform->TranslateWorld(0.0f, 64.0f);
		m_Destination = m_pTransform->GetWorldPosition();
	}

	Player::~Player()
	{
		m_pSpriteComponent = nullptr;
		m_pTransform = nullptr;
	}

	void Player::MoveNextUp(const Direction& nextDirection)
	{
		if (m_pTransform->GetWorldPosition().y - (m_MoveSpeed * m_GameTime.GetElapsedSec()) < m_Destination.y)
		{
			m_pTransform->TranslateWorld(m_Destination);
			m_Direction = nextDirection;
		}
		else
		{
			m_pTransform->MoveWorld(0, -(m_MoveSpeed * m_GameTime.GetElapsedSec()));
			m_State = State::MoveUp;
		}
	}

	void Player::MoveNextDown(const Direction& nextDirection)
	{
		if (m_pTransform->GetWorldPosition().y + (m_MoveSpeed * m_GameTime.GetElapsedSec()) > m_Destination.y)
		{
			m_pTransform->TranslateWorld(m_Destination);
			m_Direction = nextDirection;
		}
		else
		{
			m_pTransform->MoveWorld(0, +(m_MoveSpeed * m_GameTime.GetElapsedSec()));
			m_State = State::MoveDown;
		}
	}

	void Player::MoveNextLeft(const Direction& nextDirection)
	{
		if (m_pTransform->GetWorldPosition().x - (m_MoveSpeed * m_GameTime.GetElapsedSec()) < m_Destination.x)
		{
			m_pTransform->TranslateWorld(m_Destination);
			m_Direction = nextDirection;
		}
		else
		{
			m_pTransform->MoveWorld(-(m_MoveSpeed * m_GameTime.GetElapsedSec()), 0);
			m_State = State::MoveLeft;
		}
	}

	void Player::MoveNextRight(const Direction& nextDirection)
	{
		if (m_pTransform->GetWorldPosition().x + (m_MoveSpeed * m_GameTime.GetElapsedSec()) > m_Destination.x)
		{
			m_pTransform->TranslateWorld(m_Destination);
			m_Direction = nextDirection;
		}
		else
		{
			m_pTransform->MoveWorld(+(m_MoveSpeed * m_GameTime.GetElapsedSec()), 0);
			m_State = State::MoveRight;
		}
	}

	void Player::Update()
	{
		if (Input::IsKeyPressed(KEY_UP))
		{
			if (m_Destination == m_pTransform->GetWorldPosition() || m_Direction == Direction::Up || m_Direction == Direction::Down)
			{
				m_pTransform->MoveWorld(0, -(m_MoveSpeed * m_GameTime.GetElapsedSec()));

				m_Direction = Direction::Up;
				m_State = State::MoveUp;

				if (m_pTransform->GetWorldPosition().y < m_Destination.y)
				{
					m_Destination.y -= 32;
				}
			}
			else if (m_Direction == Direction::Left)
			{
				MoveNextLeft(Direction::Up);
			}
			else if (m_Direction == Direction::Right)
			{
				MoveNextRight(Direction::Up);
			}
		}
		else if (Input::IsKeyPressed(KEY_DOWN))
		{
			if (m_Destination == m_pTransform->GetWorldPosition() || m_Direction == Direction::Up || m_Direction == Direction::Down)
			{
				m_pTransform->MoveWorld(0, +(m_MoveSpeed * m_GameTime.GetElapsedSec()));

				m_Direction = Direction::Down;
				m_State = State::MoveDown;

				if (m_pTransform->GetWorldPosition().y > m_Destination.y)
				{
					m_Destination.y += 32;
				}
			}
			else if (m_Direction == Direction::Left)
			{
				MoveNextLeft(Direction::Down);
			}
			else if (m_Direction == Direction::Right)
			{
				MoveNextRight(Direction::Down);
			}
		}
		else if (Input::IsKeyPressed(KEY_LEFT))
		{
			if (m_Destination == m_pTransform->GetWorldPosition() || m_Direction == Direction::Left || m_Direction == Direction::Right)
			{
				m_pTransform->MoveWorld(-(m_MoveSpeed * m_GameTime.GetElapsedSec()), 0);

				m_Direction = Direction::Left;
				m_State = State::MoveLeft;

				if (m_pTransform->GetWorldPosition().x < m_Destination.x)
				{
					m_Destination.x -= 32;
				}
			}
			else if (m_Direction == Direction::Up)
			{
				MoveNextUp(Direction::Left);
			}
			else if (m_Direction == Direction::Down)
			{
				MoveNextDown(Direction::Left);
			}
		}
		else if (Input::IsKeyPressed(KEY_RIGHT))
		{
			if (m_Destination == m_pTransform->GetWorldPosition() || m_Direction == Direction::Left || m_Direction == Direction::Right)
			{
				m_pTransform->MoveWorld(+(m_MoveSpeed * m_GameTime.GetElapsedSec()), 0);

				m_Direction = Direction::Right;
				m_State = State::MoveRight;

				if (m_pTransform->GetWorldPosition().x > m_Destination.x)
				{
					m_Destination.x += 32;
				}
			}
			else if (m_Direction == Direction::Up)
			{
				MoveNextUp(Direction::Right);
			}
			else if (m_Direction == Direction::Down)
			{
				MoveNextDown(Direction::Right);
			}
		}
		else
		{
			m_State = State::Idle;
		}

		switch (m_State)
		{
		case Scott::Idle:
			SetClipIndex(2);
			break;
		case Scott::MoveUp:
			SetFlip(SDL_RendererFlip::SDL_FLIP_NONE);
			m_pTransform->RotateWorld(-90);
			SetClipIndex(1);
			break;
		case Scott::MoveRight:
			m_pTransform->RotateWorld(0);
			SetFlip(SDL_RendererFlip::SDL_FLIP_NONE);
			SetClipIndex(1);
			break;
		case Scott::MoveDown:
			m_pTransform->RotateWorld(90);
			SetFlip(SDL_RendererFlip::SDL_FLIP_VERTICAL);
			SetClipIndex(1);
			break;
		case Scott::MoveLeft:
			m_pTransform->RotateWorld(0);
			SetFlip(SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
			SetClipIndex(1);
			break;
		default:
			break;
		}

		// ----------------------------------- Update TileMap ------------------------------------ // 
		{
			if (m_State != State::Idle)
			{
				glm::vec2 currentPosition = m_pTransform->GetWorldPosition();

				m_GridPosX = (int)m_Destination.x / 32;
				m_GridPosY = (int)m_Destination.y / 32;

				if (m_GridPosY > 2)
				{
					m_LevelManager.SetTile(m_GridPosX, m_GridPosY, '#');
				}
			}
		}
		// --------------------------------------------------------------------------------------- //
	}

	void Player::SetFlip(const SDL_RendererFlip& flip)
	{
		if (m_Flip != flip)
		{
			m_Flip = flip;
			m_pSpriteComponent->SetFlip(flip);
		}
	}

	const glm::vec2 Player::GetGridPos()
	{
		return glm::vec2(m_GridPosX, m_GridPosY);
	}

	void Player::SetClipIndex(int index)
	{
		if (m_ClipIndex != index)
		{
			m_ClipIndex = index;
			m_pSpriteComponent->SetClipIndex(index);
		}
	}
}
