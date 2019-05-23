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
		m_Destination = m_Transform->GetWorldPosition();
	}


	Player::~Player()
	{
	}

	void Player::Update()
	{
		switch (m_State)
		{
		case State::Idle:
		{
			if (Input::IsKeyPressed(KEY_UP))
			{
				m_Destination = m_Transform->GetWorldPosition();
				m_Destination.y -= 32.0f;
				m_State = State::MoveUp;
				m_Direction = Direction::Up;
			}
			if (Input::IsKeyPressed(KEY_DOWN))
			{
				m_Destination = m_Transform->GetWorldPosition();
				m_Destination.y += 32.0f;
				m_State = State::MoveDown;
				m_Direction = Direction::Down;
			}
			if (Input::IsKeyPressed(KEY_LEFT))
			{
				m_Destination = m_Transform->GetWorldPosition();
				m_Destination.x -= 32.0f;
				m_State = State::MoveLeft;
				m_Direction = Direction::Left;
			}
			if (Input::IsKeyPressed(KEY_RIGHT))
			{
				m_Destination = m_Transform->GetWorldPosition();
				m_Destination.x += 32.0f;
				m_State = State::MoveRight;
				m_Direction = Direction::Right;
			}
		}
		break;
		case State::MoveUp:
		{
			if (m_Transform->GetWorldPosition().y - (m_MoveSpeed * m_GameTime.GetElapsedSec()) < m_Destination.y)
			{
				m_Transform->TranslateWorld(m_Destination);
				m_State = State::Idle;
			}
			else
			{
				glm::vec2 currentWorldPos = m_Transform->GetWorldPosition();
				m_Transform->TranslateWorld(currentWorldPos.x, currentWorldPos.y - (m_MoveSpeed * m_GameTime.GetElapsedSec()));
			}
		}
		break;
		case State::MoveDown:
		{
			if (m_Transform->GetWorldPosition().y + (m_MoveSpeed * m_GameTime.GetElapsedSec()) > m_Destination.y)
			{
				m_Transform->TranslateWorld(m_Destination);
				m_State = State::Idle;
			}
			else
			{
				glm::vec2 currentWorldPos = m_Transform->GetWorldPosition();
				m_Transform->TranslateWorld(currentWorldPos.x, currentWorldPos.y + (m_MoveSpeed * m_GameTime.GetElapsedSec()));
			}
		}
		break;
		case State::MoveRight:
		{
			if (m_Transform->GetWorldPosition().x + (m_MoveSpeed * m_GameTime.GetElapsedSec()) > m_Destination.x)
			{
				m_Transform->TranslateWorld(m_Destination);
				m_State = State::Idle;
			}
			else
			{
				glm::vec2 currentWorldPos = m_Transform->GetWorldPosition();
				m_Transform->TranslateWorld(currentWorldPos.x + (m_MoveSpeed * m_GameTime.GetElapsedSec()), currentWorldPos.y);
			}
		}
		break;
		case State::MoveLeft:
		{
			if (m_Transform->GetWorldPosition().x - (m_MoveSpeed * m_GameTime.GetElapsedSec()) < m_Destination.x)
			{
				m_Transform->TranslateWorld(m_Destination);
				m_State = State::Idle;
			}
			else
			{
				glm::vec2 currentWorldPos = m_Transform->GetWorldPosition();
				m_Transform->TranslateWorld(currentWorldPos.x - (m_MoveSpeed * m_GameTime.GetElapsedSec()), currentWorldPos.y);
			}
		}
		break;
		}


		// ----------------------------------- Update TileMap ------------------------------------ // 
		{
			if (m_State != State::Idle)
			{
				glm::vec2 currentPosition = m_Transform->GetWorldPosition();

				m_GridPosX = (int)m_Destination.x / 32;
				m_GridPosY = (int)m_Destination.y / 32;

				m_LevelManager.SetTile(m_GridPosX, m_GridPosY, '#');
			}
		}
		// --------------------------------------------------------------------------------------- //
	}
}
