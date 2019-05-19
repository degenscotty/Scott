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
	, m_LevelWidth{ 14 }
	, m_LevelHeight{ 18 }
	, m_TileSize{ 32 }
	, m_LevelString{}
	, m_BlackTexture{ nullptr }  
{
}

GameLayer::~GameLayer()
{
}

void GameLayer::OnAttach()
{
	m_SceneManager.CreateScene("TestScene");
	Scott::Scene* scene = m_SceneManager.GetScene("TestScene");

	std::string filePath = "../Resources/black.png";
	SDL_Surface* surface = IMG_Load(filePath.c_str());

	if (surface == nullptr)
	{
		SC_CORE_ERROR("ResourceManager::LoadTexture > Failed to load SDL_Surface: {0}", SDL_GetError());
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(m_Renderer.GetSDLRenderer(), surface);
	if (pTexture == nullptr)
	{
		SC_CORE_ERROR("ResourceManager::LoadTexture > Failed to create texture: {0}", SDL_GetError());
	}

	m_BlackTexture = pTexture;
	pTexture = nullptr;

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
		m_LevelString += L"..............";
		m_LevelString += L"..............";
		m_LevelString += L"..............";
		m_LevelString += L"..............";
		m_LevelString += L"..............";
		m_LevelString += L"..............";
		m_LevelString += L"..............";
		m_LevelString += L"..............";
		m_LevelString += L"..............";
		m_LevelString += L"......###.....";
		m_LevelString += L"..............";
		m_LevelString += L"..............";
		m_LevelString += L"..............";
		m_LevelString += L"..............";
		m_LevelString += L"..............";
		m_LevelString += L"..............";
		m_LevelString += L"..............";
		m_LevelString += L"..............";
	}
	// -------------------------------------------------------------------- //

	// --------------------------- PLAYER --------------------------------- //
	{
		m_pPlayer = new Scott::GameObject("Player");

		scene->Add(m_pPlayer);
		m_pPlayer->AddComponent(new Scott::TextureComponent("player.png"));

		m_pPlayer->GetTransform()->TranslateWorld(0, 64);
	}
	// -------------------------------------------------------------------- //
}

wchar_t GameLayer::GetTile(int x, int y)
{
	if (x >= 0 && x < m_LevelWidth && y >= 0 && y < m_LevelHeight)
	{
		return m_LevelString[y * m_LevelWidth + x];
	}
	else
	{
		return L' ';
	}
}

void GameLayer::SetTile(int x, int y, wchar_t c)
{
	if (x >= 0 && x < m_LevelWidth && y >= 0 && y < m_LevelHeight)
	{
		m_LevelString[y * m_LevelWidth + x] = c;
	}
}

void GameLayer::OnDetach()
{
}

void GameLayer::OnUpdate()
{
}

void GameLayer::Render()
{
	for (int x = 0; x < m_LevelWidth; ++x)
	{
		for (int y = 0; y < m_LevelHeight; ++y)
		{
			wchar_t tileID = GetTile(x, y);
			switch (tileID)
			{
			case L'.':
				break;
			case L'#':
				m_Renderer.RenderTexture(m_BlackTexture, x * m_TileSize, y * m_TileSize, m_TileSize, m_TileSize);
				break;
			default:
				break;
			}
		}
	}
}
