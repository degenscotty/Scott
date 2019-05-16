#pragma once
#include "Core.h"

#include "Window.h"
#include "Scott/Events/ApplicationEvent.h"
#include "Scott/LayerStack.h"
#include "Scott/ImGui/ImGuiLayer.h"

namespace Scott
{
	class SCOTT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_pWindow; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_pWindow;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;

		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	//To be defined in the client
	Application* CreateApplication();
}

