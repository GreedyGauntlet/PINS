#include "Application.h"
#include "Window.h"
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace PINS {
    bool Application::Initialize() {
        return Window::Initialize();
    }

    void Application::Run() {
        Window::CreateWindow("PINS");
        while (Window::IsOpen()) {
            glfwPollEvents();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // TODO: delete
            {
                ImGui::Begin("Hello, world!");
                ImGui::Text("This is some useful text.");
                ImGui::End();
            }

            Window::UpdateWindow();
        }
    }

    void Application::Shutdown() {
        Window::Shutdown();
    }
}