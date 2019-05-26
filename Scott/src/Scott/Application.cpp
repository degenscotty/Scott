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
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		SceneManager& sceneManager = SceneManager::GetInstance();
		Renderer& renderer = Renderer::GetInstance();
		
		SC_CORE_ASSERT(!s_Instance, "Application already excists!");
		s_Instance = this;

		m_pWindow = std::unique_ptr<Window>(Window::Create());

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

			sceneManager.Render();

			m_ImGuiLayer->End();
			
			for (Layer* layer : m_LayerStack)
			{
				layer->Render();
			}

			renderer.Render();
			
			// --------------------------------------------------------------------- //
		}
	}
}
