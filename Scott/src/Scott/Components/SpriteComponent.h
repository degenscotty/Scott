#pragma once
#include "Scott/Components/BaseComponent.h"

#include "Scott/Helpers/Texture2D.h"
#include <glm.hpp>
#include <string>

namespace Scott
{
	class Renderer;
	class TransformComponent;
	class GameObject;

	class SpriteComponent : public BaseComponent
	{
	public:
		explicit SpriteComponent(const std::string& file);
		virtual ~SpriteComponent() = default;

		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) noexcept = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) noexcept = delete;

		void Render() override;
		virtual void Initialize() {}
		virtual void Update() {}

		void SetPivot(const glm::vec2& pivot);
		void SetTexture(const std::string& file);

		Texture2D* GetTexture() { return m_pTexture; };
		const glm::vec2& GetPivot() { return m_Pivot; };

	private:
		std::string m_File;
		Texture2D* m_pTexture;
		glm::vec2 m_Pivot;

		Renderer& m_Renderer;
	};
}

