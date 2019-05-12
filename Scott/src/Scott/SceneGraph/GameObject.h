#pragma once

namespace Scott
{
	class GameObject
	{
	public:
		GameObject(const std::string& name);

		void Update();
		void Render() const;

		void SetPosition(float x, float y);

		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::string m_Name;
	};
}
