#pragma once

#include "Core.h"
#include "Scott/Events/ApplicationEvent.h"


#include "Window.h"

namespace Scott
{
	class SCOTT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_pWindow;
		bool m_Running = true;
	};

	//To be defined in the client
	Application* CreateApplication();
}

