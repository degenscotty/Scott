#pragma once

#include "Core.h"
#include "Window.h"

namespace Scott
{
	class SCOTT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> m_pWindow;
		bool m_Running = true;
	};

	//To be defined in the client
	Application* CreateApplication();
}

