#include "scpch.h"
#include "WindowsWindow.h"

#include "Scott/Events/ApplicationEvent.h"
#include "Scott/Events/MouseEvent.h"
#include "Scott/Events/KeyEvent.h"

#include "Scott/Log.h"
#include "Scott/Input.h"

namespace Scott
{
	static bool s_SDLInitialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		SC_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		// TODO: glfwTerminate on system shutdown
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			SC_CORE_ASSERT("Core::Initialize(), error when calling SDL_Init : {0}", SDL_GetError());
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		m_pWindow = SDL_CreateWindow(
			m_Data.Title.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			(int)props.Width,
			(int)props.Height,
			SDL_WINDOW_OPENGL |
			SDL_WINDOW_RESIZABLE);

		if (m_pWindow == nullptr)
		{
			SC_CORE_ERROR("Core::Initialize(), error when calling SDL_CreateWindow : {0}", SDL_GetError());
			return;
		}

		m_Context = SDL_GL_CreateContext(m_pWindow);
		if (m_Context == nullptr)
		{
			SC_CORE_ERROR("Core::Initialize( ), error when calling SDL_GL_CreateContext: {0}", SDL_GetError());
			return;
		}

		SDL_SetWindowInputFocus(m_pWindow);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown()
	{
		SDL_DestroyWindow(m_pWindow);
	}

	void WindowsWindow::OnUpdate()
	{
		//if (SDL_PollEvent(&e) != 0)
		//{
		//	WindowData& data = m_Data;

		//	// Handle the polled event
		//	switch (e.type)
		//	{
		//	case SDL_QUIT:
		//	{
		//		WindowCloseEvent event{};
		//		data.EventCallback(event);
		//	}
		//	break;
		//	case SDL_KEYDOWN:
		//	{
		//		if (e.key.repeat != 0)
		//		{
		//			KeyPressedEvent event(e.key.keysym.scancode, 1);
		//			data.EventCallback(event);
		//		}
		//		else
		//		{
		//			KeyPressedEvent event(e.key.keysym.scancode, 0);
		//			data.EventCallback(event);
		//		}
		//	}
		//	break;
		//	case SDL_KEYUP:
		//	{
		//		KeyReleasedEvent event(e.key.keysym.scancode);
		//		data.EventCallback(event);
		//	}
		//	break;
		//	case SDL_MOUSEMOTION:
		//	{
		//		MouseMovedEvent event((float)e.motion.x, (float)e.motion.y);
		//		data.EventCallback(event);
		//	}
		//	break;
		//	case SDL_MOUSEBUTTONDOWN:
		//	{
		//		MouseButtonPressedEvent event(e.button.button);
		//		data.EventCallback(event);
		//	}
		//	break;
		//	case SDL_MOUSEBUTTONUP:
		//	{
		//		MouseButtonReleasedEvent event(e.button.button);
		//		data.EventCallback(event);
		//	}
		//	break;
		//	}
		//}


		Input::Update();
		SDL_GL_SwapWindow(m_pWindow);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			SDL_GL_SetSwapInterval(1);
		else
			SDL_GL_SetSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}
