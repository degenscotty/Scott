#pragma once
#include "Scott/Helpers/Singleton.h"

#include <unordered_map>
#include "Scott/Helpers/Texture2D.h"

#include <SDL.h>

namespace Scott
{
	class ResourceManager : public Singleton<ResourceManager>
	{
	public:
		ResourceManager();
		~ResourceManager();

		Texture2D* LoadTexture(const std::string& file);
		//Font* LoadFont(const std::string& file, unsigned int size);
	private:	
		std::string m_FolderPath;

		std::unordered_map<std::string, Texture2D*> m_Textures;
		//std::unordered_map<std::string, Font*> m_Fonts;
	};
}

