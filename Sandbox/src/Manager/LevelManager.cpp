#include "scpch.h"
#include "LevelManager.h"
#include "Scott/SceneGraph/Scene.h"
#include "../DigDug/Rock.h"

namespace Scott
{
	LevelManager* LevelManager::s_Instance = nullptr;

	LevelManager::LevelManager()
		: GameObject{ "LevelManager" }
		, m_Renderer{ Renderer::GetInstance() }
		, m_LevelString{}
		, m_LevelWidth{ 14 }
		, m_LevelHeight{ 18 }
		, m_TileSize{ 32 }
		, m_pBlackTexture{ nullptr }
	{
		if (s_Instance == nullptr)
		{
			s_Instance = this;
		}
		else
		{
			SC_CORE_ERROR("LevelManager::LevelManager() > Cannot initialize LevelManager twice!");
		}

		m_LevelString += L"..............";
		m_LevelString += L"..............";
		m_LevelString += L"..............";
		m_LevelString += L"..............";
		m_LevelString += L"..............";
		m_LevelString += L"...O....OOO...";
		m_LevelString += L"..............";
		m_LevelString += L"..............";
		m_LevelString += L"..............";
		m_LevelString += L"......######..";
		m_LevelString += L"...........#..";
		m_LevelString += L"...........#..";
		m_LevelString += L"....OOOO......";
		m_LevelString += L"..............";
		m_LevelString += L"..............";
		m_LevelString += L"..............";
		m_LevelString += L"..............";
		m_LevelString += L"..............";

		std::string filePath = "../Resources/black.png";
		SDL_Surface* surface = IMG_Load(filePath.c_str());

		if (surface == nullptr)
		{
			SC_CORE_ERROR("LevelManager::LevelManager() > Failed to load SDL_Surface: {0}", SDL_GetError());
		}

		SDL_Texture* pTexture = SDL_CreateTextureFromSurface(m_Renderer.GetSDLRenderer(), surface);
		if (pTexture == nullptr)
		{
			SC_CORE_ERROR("LevelManager::LevelManager() > Failed to create SDL_Texture: {0}", SDL_GetError());
		}

		m_pBlackTexture = pTexture;
		pTexture = nullptr;
	}

	void LevelManager::InitializeLevel(Scene* scene)
	{
		for (int x = 0; x < m_LevelWidth; ++x)
		{
			for (int y = 0; y < m_LevelHeight; ++y)
			{
				wchar_t tileID = GetTile(x, y);
				switch (tileID)
				{
				case L'O':
				{
					Rock* rock = new Rock(glm::vec2(x * 32.0f, y * 32.0f));
					scene->Add(rock);
					SetTile(x, y, '.');
				}
				break;
				default:
					break;
				}
			}
		}
	}

	LevelManager::~LevelManager()
	{
		SDL_DestroyTexture(m_pBlackTexture);
	}

	wchar_t LevelManager::GetTile(int x, int y)
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

	void LevelManager::SetTile(int x, int y, wchar_t c)
	{
		if (x >= 0 && x < m_LevelWidth && y >= 0 && y < m_LevelHeight)
		{
			m_LevelString[y * m_LevelWidth + x] = c;
		}
	}

	const std::wstring& LevelManager::GetLevel()
	{
		return m_LevelString;
	}

	int LevelManager::GetWidth()
	{
		return m_LevelWidth;
	}

	int LevelManager::GetHeight()
	{
		return m_LevelHeight;
	}

	void LevelManager::Update()
	{

	}

	void LevelManager::Render()
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
					m_Renderer.RenderTexture(m_pBlackTexture, x * m_TileSize, y * m_TileSize, m_TileSize, m_TileSize);
					break;
				default:
					break;
				}
			}
		}
	}
}


