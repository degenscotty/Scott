#pragma once
#include "Scott/Helpers/Singleton.h"

#include <SDL.h>
#include "Scott/Helpers/Texture2D.h"
#include "Scott/SceneGraph/SceneManager.h"
#include "Scott/Components/Components.h"

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
		void RenderTexture(SDL_Texture* texture, int x, int y, int width, int height);
		void RenderTextureComponent(TextureComponent* textureComponent, TransformComponent* transfComponent);
		void RenderSpriteComponent(SpriteComponent* spriteComponent, TransformComponent* transfComponent);
		void RenderTextComponent(TextComponent* textureComponent, TransformComponent* transfComponent);

		SDL_Renderer* GetSDLRenderer();

	private:
		SDL_Renderer* m_pRenderer;
	};
}

