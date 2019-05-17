#include "scpch.h"
#include "Application.h"

#include "Scott/Log.h"
#include "Input.h"
#include "InputDefinitions.h"
#include "GameTime.h"
#include "Scott/SceneGraph/SceneManager.h"
#include "Scott/Renderer.h"

namespace Scott
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		SceneManager& sceneManager = SceneManager::GetInstance();
		Renderer& renderer = Renderer::GetInstance();
		
		SC_CORE_ASSERT(!s_Instance, "Application already excists!");
		s_Instance = this;

		m_pWindow = std::unique_ptr<Window>(Window::Create());
		m_pWindow->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		renderer.Initialize();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}


	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		GameTime& gameTime = GameTime::GetInstance();
		SceneManager& sceneManager = SceneManager::GetInstance();
		Renderer& renderer = Renderer::GetInstance();

		while (!Input::Quit())
		{
			gameTime.Update();

			m_pWindow->OnUpdate();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(); 
			}

			sceneManager.Update();
			
			// --------------------------- Rendering -------------------------------- //

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();

			renderer.ClearBuffer();

			m_ImGuiLayer->End();

			for (Layer* layer : m_LayerStack)
			{
				layer->Render();
			}

			renderer.Render();

			// --------------------------------------------------------------------- //
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
