#include "scpch.h"
#include "GameLayer.h"
#include "Scott/Components/Components.h"
#include "Scott/SceneGraph/Scene.h"
#include "Scott/Input.h"
#include "Scott/InputDefinitions.h"

GameLayer::GameLayer()
	: m_SceneManager{ Scott::SceneManager::GetInstance() }
	, m_pTestObject{ nullptr }
{
}

GameLayer::~GameLayer()
{
}

void GameLayer::OnAttach()
{
	m_SceneManager.CreateScene("TestScene");
	Scott::Scene* scene = m_SceneManager.GetScene("TestScene");

	m_pTestObject = new Scott::GameObject("TestObject");

	scene->Add(m_pTestObject);

	m_pTestObject->AddComponent(new Scott::TextureComponent());
	Scott::TextureComponent* texComponent = m_pTestObject->GetComponent<Scott::TextureComponent>();

	texComponent->SetTexture("TestPNG.png");
	texComponent->SetPivot(glm::vec2(640.0f, 360.0f));
	m_pTestObject->GetTransform()->TranslateWorld(640.0f, 360.0f);
	m_pTestObject->GetTransform()->ScaleWorld(0.2f, 0.2f);
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
	glLineWidth(2.0f);
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(500, 500);
		glVertex2f(500, 510);
		glVertex2f(510, 510);
		glVertex2f(510, 500);
	}
	glEnd();
}
