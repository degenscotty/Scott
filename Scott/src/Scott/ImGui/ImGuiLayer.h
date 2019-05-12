#pragma once

#include "Scott/Layer.h"

namespace Scott
{
	class SCOTT_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnImGuiRender();
		
		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
		bool show_demo_window;
	};
}