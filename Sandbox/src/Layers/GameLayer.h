#pragma once
#include "Scott/Layer.h"
#include "Scott/SceneGraph/SceneManager.h"
#include "Scott/SceneGraph/GameObject.h"
#include "Scott/Manager/LevelManager.h"
#include "Scott/DigDug/Player.h"
#include "Scott/Renderer.h"

class GameLayer : public Scott::Layer
{
public:
	GameLayer();
	~GameLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate() override;
	void Render() override;

private:
	Scott::SceneManager& m_SceneManager;
	Scott::Renderer& m_Renderer;

	Scott::GameObject* m_pTestObject;
	Scott::GameObject* m_pTextObject;
	Scott::Player* m_pPlayer;

	Scott::LevelManager* m_pLevelManager;
};

