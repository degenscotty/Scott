#pragma once
#include "Scott/Helpers/Singleton.h"

#include <SDL.h>
#include "Scott/Helpers/Texture2D.h"
#include "Scott/SceneGraph/SceneManager.h"
#include "Scott/Components/TextureComponent.h"
#include "Scott/Components/TransformComponent.h"

namespace Scott
{
	class Renderer : public Singleton<Renderer>
	{
	public:
		Renderer();
		~Renderer();

		void Initialize();
		void Render();
		void ClearBuffer();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTextureComponent(TextureComponent* texComponent, TransformComponent* transfComponent);
		//void RenderTextComponent(TextComponent* component);

		SDL_Renderer* GetSDLRenderer();

	private:
		SDL_Renderer* m_pRenderer;
		SceneManager& m_SceneManager;
	};
}

