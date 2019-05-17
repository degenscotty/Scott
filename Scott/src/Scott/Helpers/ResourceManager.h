#pragma once
#include "Scott/Helpers/Singleton.h"

#include <unordered_map>
#include "Scott/Helpers/Texture2D.h"
#include "Scott/Helpers/Font.h"

#include <SDL.h>

namespace Scott
{
	class ResourceManager : public Singleton<ResourceManager>
	{
	public:
		ResourceManager();
		~ResourceManager();

		Texture2D* LoadTexture(const std::string& file);
		Font* LoadFont(const std::pair<std::string, unsigned int>& fontData);
	private:
		struct pair_hash
		{
			template <class T1, class T2>
			size_t operator()(const std::pair<T1, T2>& pair) const
			{
				return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
			}
		};

		std::string m_FolderPath;

		std::unordered_map<std::string, Texture2D*> m_Textures;
		std::unordered_map<std::pair<std::string, unsigned int>, Font*, pair_hash> m_Fonts;

	};

}

