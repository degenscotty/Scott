#pragma once
#include "Scott/Input.h"
#include "Scott/InputDefinitions.h"

namespace Scott
{
	class InputManager : public Input
	{
	public:

		void UpdateImpl();

		bool IsKeyPressedImpl(int keycode) override;
		bool IsMouseButtonPressedImpl(int button) override;

		float GetMouseXImpl() override;
		float GetMouseYImpl() override;

		std::pair<float, float> GetMousePosImpl() override;


	private:
		SDL_Event e;

		bool m_KeyDown[KEYBOARD_SIZE];
		bool m_KeyUp[KEYBOARD_SIZE];

		bool m_MouseDown[MOUSE_MAX];
		bool m_MouseUp[MOUSE_MAX];

		int m_MouseX;
		int m_MouseY;

	};
}

