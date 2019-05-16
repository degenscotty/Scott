#include "scpch.h"
#include "InputManager.h"

namespace Scott
{
	Input* Input::s_Instance = new InputManager();

	void InputManager::UpdateImpl()
	{
		for (int i{ 0 }; i < KEYBOARD_SIZE; i++)
		{
			if (m_KeyDown[i] == true && m_KeyUp[i] == true)
			{
				m_KeyDown[i] = false;
			}
			m_KeyUp[i] = false;
		}

		for (int i{ 0 }; i < MOUSE_MAX; i++)
		{
			m_MouseDown[i] = false;
			m_MouseDown[i] = false;
		}


		if (SDL_PollEvent(&e) != 0)
		{
			// Handle the polled event
			switch (e.type)
			{
			case SDL_KEYDOWN:
			{
				if (e.key.repeat != 0)
				{
					m_KeyDown[e.key.keysym.scancode] = true;
				}
				else
				{
					m_KeyDown[e.key.keysym.scancode] = true;
				}
			}
			break;
			case SDL_KEYUP:
			{
				m_KeyUp[e.key.keysym.scancode] = true;
			}
			break;
			case SDL_MOUSEMOTION:
			{
				m_MouseX = e.motion.x;
				m_MouseY = e.motion.y;
			}
			break;
			case SDL_MOUSEBUTTONDOWN:
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					m_MouseDown[MOUSE_LEFT] = true;
				}
				if (e.button.button == SDL_BUTTON_RIGHT)
				{
					m_MouseDown[MOUSE_RIGHT] = true;
				}
			}
			break;
			case SDL_MOUSEBUTTONUP:
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					m_MouseUp[MOUSE_LEFT] = true;
				}
				if (e.button.button == SDL_BUTTON_RIGHT)
				{
					m_MouseUp[MOUSE_RIGHT] = true;
				}
			}
			break;
			}
		}
	}

	bool InputManager::IsKeyPressedImpl(int keycode)
	{
		return m_KeyDown[keycode];
	}

	bool InputManager::IsMouseButtonPressedImpl(int button)
	{
		return m_MouseDown[button];
	}

	float InputManager::GetMouseXImpl()
	{
		return (float)m_MouseX;
	}

	float InputManager::GetMouseYImpl()
	{
		return (float)m_MouseY;
	}

	std::pair<float, float> InputManager::GetMousePosImpl()
	{
		return {(float)m_MouseX, (float)m_MouseY};
	}
}
