#pragma once

#include "Scott/Core.h"

namespace Scott
{
	class SCOTT_API Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }

		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }

		inline static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }

		static void Update() { s_Instance->UpdateImpl(); };

	protected:
		virtual bool IsKeyPressedImpl (int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;

		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

		virtual std::pair<float, float> GetMousePosImpl() = 0;

		virtual void UpdateImpl() = 0;
	private:
		static Input* s_Instance;
	};
}

