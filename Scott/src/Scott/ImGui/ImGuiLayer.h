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
		void OnUpdate() override;
		void OnEvent(Event& event) override;


	private:
		float m_Time = 0.0f;
	};
}