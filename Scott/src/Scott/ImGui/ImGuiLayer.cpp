#include "scpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/SDL/ImGuiSDLRenderer.h"
#include "Platform/SDL/ImGuiOpenGLRenderer.h"
#include "Platform/SDL/imgui_sdl.h"

#include "Scott/Application.h"
#include "Scott/GameTime.h"
#include "Scott/Renderer.h"

namespace Scott
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
		, show_demo_window{ false }
		, m_Counter{ 60 }
		, m_Fps{}
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
		Application& app = Application::get();
		Renderer& renderer = Renderer::GetInstance();

		//IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		//ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

		ImGui::StyleColorsDark();

		ImGui_ImplSDL2_InitForOpenGL(app.GetWindow().GetSDLWindow(), app.GetWindow().GetSDLContext());
		//ImGui_ImplOpenGL2_Init();

		ImGuiSDL::Initialize(renderer.GetSDLRenderer(), 1280, 720);

		//SDL_Texture* texture = SDL_CreateTexture(renderer.GetSDLRenderer(), SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 100, 100);
		//{
		//	SDL_SetRenderTarget(renderer.GetSDLRenderer(), texture);
		//	SDL_SetRenderDrawColor(renderer.GetSDLRenderer(), 255, 0, 255, 255);
		//	SDL_RenderClear(renderer.GetSDLRenderer());
		//	SDL_SetRenderTarget(renderer.GetSDLRenderer(), nullptr);
		//}
	}

	void ImGuiLayer::OnDetach()
	{
		ImGuiSDL::Deinitialize();

		//ImGui_ImplOpenGL2_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin()
	{
		Application& app = Application::get();

		//ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplSDL2_NewFrame(app.GetWindow().GetSDLWindow());
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		Application& app = Application::get();

		//ImGuiIO& io = ImGui::GetIO();
		//io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		ImGui::Render();
		//ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
		ImGuiSDL::Render(ImGui::GetDrawData());

		//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		//{
		//	GLFWwindow* backup_current_context = glfwGetCurrentContext();
		//	ImGui::UpdatePlatformWindows();
		//	ImGui::RenderPlatformWindowsDefault();
		//	glfwMakeContextCurrent(backup_current_context);
		//}
	}

	void ImGuiLayer::OnImGuiRender()
	{
		++m_Counter;
		if (m_Counter >= 144)
		{
			m_Fps = GameTime::GetInstance().GetFPS();
			m_Counter = 0;
		}

		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		ImGui::Begin("FPS Counter");
		//ImGui::Checkbox("Demo Window", &show_demo_window);

		ImGui::Text("%.0f FPS", ImGui::GetIO().Framerate);
		ImGui::Text("%.0f Times PS GameLoop", (float)m_Fps);
		ImGui::End();
	}
}