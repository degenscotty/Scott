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
		m_pTestObject->AddComponent(new Scott::TextureComponent("background.png"));
		Scott::TextureComponent* textureComponent = m_pTestObject->GetComponent<Scott::TextureComponent>();

		m_pTestObject->GetTransform()->TranslateWorld(0, 0);
		m_pTestObject->GetTransform()->ScaleWorld(2, 2);
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

	// --------------------------- PNG ----------------------------------- //
	{





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
