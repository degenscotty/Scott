#include "Application.h"

#include "Scott/Events/ApplicationEvent.h"
#include "Scott/Log.h"

namespace Scott
{
	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		SC_TRACE(e);

		while (true);
	}
}
