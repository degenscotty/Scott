#include "scpch.h"
#include "GameLayer.h"
#include "Scott/SceneGraph/GameObject.h"
#include "Scott/Components/Components.h"
#include "Scott/SceneGraph/Scene.h"


GameLayer::GameLayer()
	: m_SceneManager{ Scott::SceneManager::GetInstance() }
{
}

GameLayer::~GameLayer()
{
}

void GameLayer::OnAttach()
{
	m_SceneManager.CreateScene("TestScene");
	Scott::Scene* scene = m_SceneManager.GetScene("TestScene");

	Scott::GameObject* testObject = new Scott::GameObject("TestObject");

	scene->Add(testObject);

	testObject->AddComponent(new Scott::TextureComponent());
	Scott::TextureComponent* texComponent = testObject->GetComponent<Scott::TextureComponent>();

	texComponent->SetTexture("TestPNG.png");
	testObject->GetTransform()->Translate(640.0f, 360.0f);
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
