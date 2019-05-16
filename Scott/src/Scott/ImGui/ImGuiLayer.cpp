#include "scpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/SDL/ImGuiSDLRenderer.h"
#include "Platform/SDL/ImGuiOpenGLRenderer.h"

#include "Scott/Application.h"
#include "Scott/GameTime.h"

namespace Scott
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
		Application& app = Application::get();

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

		ImGui::StyleColorsDark();

		ImGui_ImplSDL2_InitForOpenGL(app.GetWindow().GetSDLWindow(), app.GetWindow().GetSDLContext());
		ImGui_ImplOpenGL2_Init();
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL2_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin()
	{
		Application& app = Application::get();

		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplSDL2_NewFrame(app.GetWindow().GetSDLWindow());
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		Application& app = Application::get();

		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());
	
		ImGui::Render();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	
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
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		{
			ImGui::Begin("Test Window");                         
			ImGui::Checkbox("Demo Window", &show_demo_window);

			ImGui::Text("%.0f FPS", (float)GameTime::GetInstance().GetFPS());
			ImGui::End();
		}
	}
}