#pragma once
#include "Scott/SceneGraph/GameObject.h"
#include "Scott/Renderer.h"

namespace Scott
{
	class LevelManager : public GameObject
	{
	public:
		LevelManager();
		~LevelManager();

		LevelManager(const LevelManager& other) = delete;
		LevelManager(LevelManager&& other) = delete;
		LevelManager& operator=(const LevelManager& other) = delete;
		LevelManager& operator=(LevelManager&& other) = delete;

		void Update() override;
		void Render() override;

		wchar_t GetTile(int x, int y);
		void SetTile(int x, int y, wchar_t c);

		static inline LevelManager& GetInstance() { return *s_Instance; };
	private:
		Renderer& m_Renderer;

		int m_LevelWidth;
		int m_LevelHeight;

		int m_TileSize;

		std::wstring m_LevelString;
		SDL_Texture* m_pBlackTexture;

		static LevelManager* s_Instance;
	};
}

