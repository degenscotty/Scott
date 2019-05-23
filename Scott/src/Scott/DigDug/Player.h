#pragma once
#include "Scott/SceneGraph/GameObject.h"
#include "Scott/GameTime.h"
#include "Scott/Manager/LevelManager.h"

namespace Scott
{
	enum State
	{
		Idle,
		MoveUp,
		MoveRight,
		MoveDown,
		MoveLeft
	};

	enum Direction
	{
		Up,
		Down,
		Left,
		Right
	};

	class Player : public GameObject
	{
	public:
		Player();
		~Player();

		void Update() override;

		Player(const Player& other) = delete;
		Player(Player&& other) = delete;
		Player& operator=(const Player& other) = delete;
		Player& operator=(Player&& other) = delete;

	private:
		GameTime& m_GameTime;
		LevelManager& m_LevelManager;
		
		State m_State;
		Direction m_Direction;
		float m_MoveSpeed;

		TransformComponent* m_Transform;
		glm::vec2 m_Destination;

		int m_GridPosX;
		int m_GridPosY;
	};
}

