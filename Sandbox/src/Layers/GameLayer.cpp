#include "scpch.h"
#include "GameLayer.h"
#include "Scott/Components/Components.h"
#include "Scott/SceneGraph/Scene.h"
#include "Scott/Input.h"
#include "Scott/InputDefinitions.h"

GameLayer::GameLayer()
	: m_SceneManager{ Scott::SceneManager::GetInstance() }
	, m_Renderer{ Scott::Renderer::GetInstance() }
	, m_pTestObject{ nullptr }
	, m_pTextObject{ nullptr }
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
		m_pTestObject->AddComponent(new Scott::TextureComponent("TestPNG.png"));
		Scott::TextureComponent* textureComponent = m_pTestObject->GetComponent<Scott::TextureComponent>();

		m_pTestObject->GetTransform()->TranslateWorld(400.0f, 360.0f);
		m_pTestObject->GetTransform()->ScaleWorld(0.2f, 0.2f);
	}
	// -------------------------------------------------------------------- //

	// --------------------------- TEXT ----------------------------------- //
	{
		m_pTextObject = new Scott::GameObject("TextObject");

		scene->Add(m_pTextObject);
		m_pTextObject->AddComponent(new Scott::TextComponent("WRESTLEMANIA.ttf", "Scott Engine", 64));
		Scott::TextComponent* textComponent = m_pTextObject->GetComponent<Scott::TextComponent>();
		textComponent->SetColor(SDL_Color({ 125, 25, 25, 255 }));

		m_pTextObject->GetTransform()->TranslateWorld(640.0f, 360.0f);
	}
	// -------------------------------------------------------------------- //
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate()
{
	if (Scott::Input::IsKeyPressed(KEY_W))
	{
		glm::vec2 worldPos = m_pTestObject->GetTransform()->GetWorldPosition();
		m_pTestObject->GetTransform()->TranslateWorld(worldPos + glm::vec2(0.0f, -1.0f));
	}
	if (Scott::Input::IsKeyPressed(KEY_A))
	{
		glm::vec2 worldPos = m_pTestObject->GetTransform()->GetWorldPosition();
		m_pTestObject->GetTransform()->TranslateWorld(worldPos + glm::vec2(-1.0f, 0.0f));
	}
	if (Scott::Input::IsKeyPressed(KEY_D))
	{
		glm::vec2 worldPos = m_pTestObject->GetTransform()->GetWorldPosition();
		m_pTestObject->GetTransform()->TranslateWorld(worldPos + glm::vec2(1.0f, 0.0f));
	}
	if (Scott::Input::IsKeyPressed(KEY_S))
	{
		glm::vec2 worldPos = m_pTestObject->GetTransform()->GetWorldPosition();
		m_pTestObject->GetTransform()->TranslateWorld(worldPos + glm::vec2(0.0f, 1.0f));
	}
}

void GameLayer::Render()
{
}
