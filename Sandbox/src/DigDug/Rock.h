#pragma once

#include "Scott/SceneGraph/GameObject.h"
#include "Scott/GameTime.h"
#include "../Manager/LevelManager.h"

namespace Scott
{
	enum State
	{
		Idle,
		Falling,
		Braking
	};

	class Rock : public GameObject
	{
	public:
		Rock(const glm::vec2& position);
		~Rock();

		Rock(const Rock& other) = delete;
		Rock(Rock&& other) = delete;
		Rock& operator=(const Rock& other) = delete;
		Rock& operator=(Rock&& other) = delete;

		void Update() override;

		void SetClipIndex(int index);
	private:
		GameTime& m_GameTime;
		LevelManager& m_LevelManager;

		TransformComponent* m_pTransform;
		SpriteComponent* m_pSpriteComponent;

		State m_State;
		int m_ClipIndex;

		int m_GridPosX;
		int m_GridPosY;

		float m_MoveSpeed;
		glm::vec2 m_Destination;
	};
}

