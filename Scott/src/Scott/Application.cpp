#include "scpch.h"
#include "Application.h"

#include "Scott/Events/ApplicationEvent.h"
#include "Scott/Log.h"

namespace Scott
{
	Application::Application()
	{
		m_pWindow = std::make_unique<Window>(Window::Create());
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_pWindow->OnUpdate();
		}
	}
}
