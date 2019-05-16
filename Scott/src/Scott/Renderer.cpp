#include "scpch.h"
#include "Renderer.h"
#include "Application.h"

namespace Scott
{
	Renderer::Renderer()
		: m_pRenderer{ nullptr }
		, m_SceneManager{ SceneManager::GetInstance() }
	{
	}

	Renderer::~Renderer()
	{
		SDL_DestroyRenderer(m_pRenderer);
		m_pRenderer = nullptr;

		IMG_Quit();
	}

	void Renderer::Initialize()
	{
		m_pRenderer = SDL_CreateRenderer(Application::get().GetWindow().GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (m_pRenderer == nullptr)
		{
			SC_CORE_ERROR("WindowsWindow::Initialize( ) > error when calling SDL_CreateRenderer: {0}", SDL_GetError());
			return;
		}

		SDL_SetRenderDrawColor(m_pRenderer, 150, 150, 150, 255);

		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			SC_CORE_ERROR("WindowsWindow::Initialize( ) > error when calling IMG_Init: {0}", IMG_GetError());
			return;
		}
	}

	SDL_Renderer* Renderer::GetSDLRenderer()
	{
		return m_pRenderer;
	}

	void Renderer::Render()
	{
		SDL_RenderClear(m_pRenderer);

		m_SceneManager.Render();

		SDL_RenderPresent(m_pRenderer);
	}

	void Renderer::RenderTexture(const Texture2D& texture, float x, float y) const
	{

	}

	void Renderer::RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const
	{

	}

	void Renderer::RenderTextureComponent(TextureComponent* texComponent, TransformComponent* transfComponent)
	{
		SDL_Rect dest;
		TransformComponent* pTransform = transfComponent;
		Texture2D* pTex = texComponent->GetTexture();

		dest.x = static_cast<int>(pTransform->GetWorldPosition().x);
		dest.y = static_cast<int>(pTransform->GetWorldPosition().y);

		SDL_QueryTexture(pTex->GetSDLTexture(), nullptr, nullptr, &dest.w, &dest.h);

		dest.w = int(dest.w * pTransform->GetWorldScale().x);
		dest.h = int(dest.h * pTransform->GetWorldScale().y);

		SDL_Point* pPivot = new SDL_Point();
		pPivot->x = static_cast<int>(texComponent->GetPivot().x);
		pPivot->y = static_cast<int>(texComponent->GetPivot().y);

		//if (texComponent->GetPivot())
		//{
		//	pPivot = new SDL_Point();
		//	pPivot->x = static_cast<int>(transfComponent->GetPivot()->x);
		//	pPivot->y = static_cast<int>(transfComponent->GetPivot()->y);
		//}
		SDL_RenderCopyEx(GetSDLRenderer(), pTex->GetSDLTexture(), nullptr, &dest, pTransform->GetWorldRotation(), pPivot, SDL_FLIP_NONE);
	}
}
