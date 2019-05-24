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
		, m_Transform{ GetComponent<TransformComponent>() }
		, m_GameTime{ GameTime::GetInstance() }
		, m_LevelManager{ LevelManager::GetInstance() }
	{
		AddComponent(new TextureComponent("player.png"));
		m_Transform->TranslateWorld(0.0f, 64.0f);
		m_Destination = m_Transform->GetWorldPosition();
	}


	Player::~Player()
	{
	}

	void Player::MoveNextUp(const Direction& nextDirection)
	{
		if (m_Transform->GetWorldPosition().y - (m_MoveSpeed * m_GameTime.GetElapsedSec()) < m_Destination.y)
		{
			m_Transform->TranslateWorld(m_Destination);
			m_Direction = nextDirection;
		}
		else
		{
			m_Transform->MoveWorld(0, -(m_MoveSpeed * m_GameTime.GetElapsedSec()));
		}
	}

	void Player::MoveNextDown(const Direction& nextDirection)
	{
		if (m_Transform->GetWorldPosition().y + (m_MoveSpeed * m_GameTime.GetElapsedSec()) > m_Destination.y)
		{
			m_Transform->TranslateWorld(m_Destination);
			m_Direction = nextDirection;
		}
		else
		{
			m_Transform->MoveWorld(0, +(m_MoveSpeed * m_GameTime.GetElapsedSec()));
		}
	}

	void Player::MoveNextLeft(const Direction& nextDirection)
	{
		if (m_Transform->GetWorldPosition().x - (m_MoveSpeed * m_GameTime.GetElapsedSec()) < m_Destination.x)
		{
			m_Transform->TranslateWorld(m_Destination);
			m_Direction = nextDirection;
		}
		else
		{
			m_Transform->MoveWorld(-(m_MoveSpeed * m_GameTime.GetElapsedSec()), 0);
		}
	}

	void Player::MoveNextRight(const Direction& nextDirection)
	{
		if (m_Transform->GetWorldPosition().x + (m_MoveSpeed * m_GameTime.GetElapsedSec()) > m_Destination.x)
		{
			m_Transform->TranslateWorld(m_Destination);
			m_Direction = nextDirection;
		}
		else
		{
			m_Transform->MoveWorld(+(m_MoveSpeed * m_GameTime.GetElapsedSec()), 0);
		}
	}

	void Player::Update()
	{
		if (Input::IsKeyPressed(KEY_UP))
		{
			if (m_Destination == m_Transform->GetWorldPosition() || m_Direction == Direction::Up || m_Direction == Direction::Down)
			{
				m_Transform->MoveWorld(0, -(m_MoveSpeed * m_GameTime.GetElapsedSec()));

				m_Direction = Direction::Up;
				m_State = State::MoveUp;

				if (m_Transform->GetWorldPosition().y < m_Destination.y)
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
			if (m_Destination == m_Transform->GetWorldPosition() || m_Direction == Direction::Up || m_Direction == Direction::Down)
			{
				m_Transform->MoveWorld(0, +(m_MoveSpeed * m_GameTime.GetElapsedSec()));

				m_Direction = Direction::Down;
				m_State = State::MoveDown;

				if (m_Transform->GetWorldPosition().y > m_Destination.y)
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
			if (m_Destination == m_Transform->GetWorldPosition() || m_Direction == Direction::Left || m_Direction == Direction::Right)
			{
				m_Transform->MoveWorld(-(m_MoveSpeed * m_GameTime.GetElapsedSec()), 0);

				m_Direction = Direction::Left;
				m_State = State::MoveLeft;

				if (m_Transform->GetWorldPosition().x < m_Destination.x)
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
			if (m_Destination == m_Transform->GetWorldPosition() || m_Direction == Direction::Left || m_Direction == Direction::Right)
			{
				m_Transform->MoveWorld(+(m_MoveSpeed * m_GameTime.GetElapsedSec()), 0);

				m_Direction = Direction::Right;
				m_State = State::MoveRight;

				if (m_Transform->GetWorldPosition().x > m_Destination.x)
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

		// ----------------------------------- Update TileMap ------------------------------------ // 
		{
			if (m_State != State::Idle)
			{
				glm::vec2 currentPosition = m_Transform->GetWorldPosition();

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
}
