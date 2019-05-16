#pragma once
#include "Scott/Components/BaseComponent.h"

#include "Scott/Helpers/Texture2D.h"
#include <glm.hpp>

namespace Scott
{
	class Renderer;
	class TransformComponent;
	class GameObject;

	class TextureComponent : public BaseComponent
	{
	public:
		TextureComponent();
		virtual ~TextureComponent() = default;

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) noexcept = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) noexcept = delete;

		void Render() override;
		virtual void Initialize() {}
		virtual void Update() {}


		void SetPivot(const glm::vec2& pivot);
		void SetTexture(const std::string& file);

		Texture2D* GetTexture() { return m_pTexture; };
		const glm::vec2& GetPivot() { return m_Pivot; };

	private:
		Texture2D* m_pTexture;
		glm::vec2 m_Pivot;

		Renderer& m_Renderer;
	};
}

