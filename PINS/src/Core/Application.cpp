#include "Application.h"
#include "Window.h"
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "../Panels/CommandPanel.h"
#include "../Panels/ClientHierarchyPanel.h"
#include "../Panels/ClientDetailsPanel.h"

namespace PINS {

    Application::Application() {
        m_Panels = {
            new CommandPanel(),
			new ClientHierarchyPanel(),
			new ClientDetailsPanel(),
        };
    }

    bool Application::Initialize() {
        return Window::Initialize();
    }

    void Application::Run() {
        // create window
        Window::CreateWindow("PINS");

        // initialize panels
        for (auto panel : m_Panels) {
            panel->Initialize();
        }

        // update loop
        while (Window::IsOpen()) {
            glfwPollEvents();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            static bool dockspace_open = true;
		    static bool opt_fullscreen = true;
		    static bool opt_padding = false;
		    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
		    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		    if (opt_fullscreen) {
			    const ImGuiViewport* viewport = ImGui::GetMainViewport();
			    ImGui::SetNextWindowPos(viewport->WorkPos);
			    ImGui::SetNextWindowSize(viewport->WorkSize);
			    ImGui::SetNextWindowViewport(viewport->ID);
			    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		    } else {
			    dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		    }

		    if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) window_flags |= ImGuiWindowFlags_NoBackground;

		    if (!opt_padding) ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		    ImGui::Begin("DockSpace", &dockspace_open, window_flags);
		    if (!opt_padding) ImGui::PopStyleVar();

		    if (opt_fullscreen) ImGui::PopStyleVar(2);

		    ImGuiIO& io = ImGui::GetIO();
		    ImGuiStyle& style = ImGui::GetStyle();
		    style.WindowMinSize.x = 380.0f;
		    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		    }

		    style.WindowMinSize.x = 32.0f;

		    if (ImGui::BeginMenuBar()) {
			    if (ImGui::BeginMenu("File")) {
				    ImGui::MenuItem("New", "Ctrl+N");
				    ImGui::MenuItem("Open...", "Ctrl+O");
				    ImGui::EndMenu();
			    }

			    ImGui::SameLine(ImGui::GetWindowSize().x);
			    std::string lastSaved = "Last Saved 0s ago";
			    ImGui::SetCursorPosX(ImGui::GetCursorPosX() - ImGui::CalcTextSize(lastSaved.c_str()).x - 10);
			    ImGui::PushStyleColor(ImGuiCol_Text, {0.6, 0.6, 0.6, 1});
			    ImGui::Text(lastSaved.c_str());
			    ImGui::PopStyleColor();

			    ImGui::SameLine((ImGui::GetWindowSize().x) / 2);
			    static std::string viewportName = "PINS";
			    ImGui::SetCursorPosX(ImGui::GetCursorPosX() - ImGui::CalcTextSize(viewportName.c_str()).x / 2);
			    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
			    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));
			    static bool s_RenameScene = false;
			    if (!s_RenameScene) {
				    if (ImGui::Button(viewportName.c_str())) {
					    s_RenameScene = true;
				    }
			    } else {
				    static char newSceneName[256] = "";
				    strncpy(newSceneName, viewportName.c_str(), 256);
				    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0, 0, 0, 0));
				    ImGui::SetNextItemWidth(500);
				    s_RenameScene = !(ImGui::InputText("##Rename", newSceneName, 256, ImGuiInputTextFlags_EnterReturnsTrue));
				    ImGui::PopStyleColor();
				    if (!s_RenameScene)
					    viewportName = newSceneName;
			    }
			    ImGui::PopStyleColor(3);

			    ImGui::EndMenuBar();
		    }

            // update panels
            for (auto panel : m_Panels) {
                panel->Update();
            }

		    ImGui::End();

            Window::UpdateWindow();
        }
    }

    void Application::Shutdown() {
        Window::Shutdown();
    }
}