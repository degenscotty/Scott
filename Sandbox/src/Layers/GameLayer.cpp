#include "scpch.h"
#include "GameLayer.h"
#include "Scott/Components/Components.h"
#include "Scott/SceneGraph/Scene.h"
#include "Scott/Input.h"
#include "Scott/InputDefinitions.h"
#include "imgui.h"

GameLayer::GameLayer()
	: m_SceneManager{ Scott::SceneManager::GetInstance() }
	, m_Renderer{ Scott::Renderer::GetInstance() }
	, m_pTestObject{ nullptr }
	, m_pTextObject{ nullptr }
	, m_pLevelManager{ nullptr }
	, m_pPlayer{ nullptr }
{
}

GameLayer::~GameLayer()
{
}

void GameLayer::OnAttach()
{
	m_SceneManager.CreateScene("TestScene");
	Scott::Scene* scene = m_SceneManager.GetScene("TestScene");

	// --------------------------- PNG ----------------------------------- //
	{
		m_pTestObject = new Scott::GameObject("TestObject");

		scene->Add(m_pTestObject);
		m_pTestObject->AddComponent(new Scott::TextureComponent("background.png"));
		Scott::TextureComponent* textureComponent = m_pTestObject->GetComponent<Scott::TextureComponent>();

		m_pTestObject->GetTransform()->TranslateWorld(0, 0);
	}
	// -------------------------------------------------------------------- //

	// --------------------------- TEXT ----------------------------------- //
	{
		m_pTextObject = new Scott::GameObject("TextObject");

		scene->Add(m_pTextObject);
		m_pTextObject->AddComponent(new Scott::TextComponent("digdug.ttf", "Scott Engine", 36));
		Scott::TextComponent* textComponent = m_pTextObject->GetComponent<Scott::TextComponent>();
		textComponent->SetColor(SDL_Color({ 255, 184, 0, 255 }));

		m_pTextObject->GetTransform()->TranslateWorld(0, 0);
	}
	// -------------------------------------------------------------------- //

	// --------------------------- LEVEL ---------------------------------- //
	{
		m_pLevelManager = new Scott::LevelManager();

		scene->Add(m_pLevelManager);

		m_pLevelManager->InitializeLevel(scene);
	}
	// -------------------------------------------------------------------- //

	// --------------------------- PLAYER --------------------------------- //
	{
		m_pPlayer = new Scott::Player();

		scene->Add(m_pPlayer);

		m_pPlayer->GetTransform()->TranslateWorld(0, 64);
	}
	// -------------------------------------------------------------------- //
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate()
{
}

void GameLayer::Render()
{
}

void GameLayer::OnImGuiRender()
{
	glm::vec2 gridPos = m_pPlayer->GetGridPos();

	ImGui::Begin("DEBUG");

	ImGui::Text("[NextX: %.0f, NextY: %.0f]", gridPos.x, gridPos.y);
	ImGui::End();
}
