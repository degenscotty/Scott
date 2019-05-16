#include "scpch.h"
#include "ResourceManager.h"
#include "Scott/Renderer.h"


namespace Scott
{
	ResourceManager::ResourceManager()
		: m_FolderPath("../Resources/")
	{
	}

	ResourceManager::~ResourceManager()
	{
		for (auto texture : m_Textures)
		{
			delete texture.second;
		}
		//for (auto font : m_Fonts)
		//{
		//	delete font.second;
		//}
	}

	Texture2D* ResourceManager::LoadTexture(const std::string& file)
	{
		Renderer& renderer = Renderer::GetInstance();

		if (renderer.GetSDLRenderer())
		{
			if (m_Textures[file]) return m_Textures[file];

			std::string filePath = m_FolderPath + file;
			SDL_Surface* surface = IMG_Load(filePath.c_str());

			if (surface == nullptr)
			{
				SC_CORE_ERROR("ResourceManager::LoadTexture > Failed to load SDL_Surface: {0}", SDL_GetError());
			}

			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer.GetSDLRenderer(), surface);
			if (texture == nullptr)
			{
				SC_CORE_ERROR("ResourceManager::LoadTexture > Failed to create texture: {0}", SDL_GetError());
			}
			m_Textures[file] = new Texture2D(texture);
			return m_Textures[file];
		}
		else
		{
			SC_CORE_ERROR("ResourceManager::LoadTexture > Renderer is invalid!");
		}
	}
}
