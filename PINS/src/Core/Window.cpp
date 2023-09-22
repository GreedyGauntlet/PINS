#include "Window.h"
#define GL_SILENCE_DEPRECATION
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <GLFW/glfw3.h>

static GLFWwindow* s_Window;
static std::string s_GLSL_VERSION;
static ImVec4 s_ClearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

namespace PINS {
    bool Window::Initialize() {
        glfwSetErrorCallback(glfw_error_callback);
        if (!glfwInit()) return false;

        // Decide GL+GLSL versions
        #if defined(IMGUI_IMPL_OPENGL_ES2)
            // GL ES 2.0 + GLSL 100
            s_GLSL_VERSION = "#version 100";
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        #elif defined(__APPLE__)
            // GL 3.2 + GLSL 150
            s_GLSL_VERSION = "#version 150";
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
        #else
            // GL 3.0 + GLSL 130
            s_GLSL_VERSION = "#version 130";
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        #endif

       return true;
    }

    void Window::CreateWindow(std::string name) {
        // Create window with graphics context
         s_Window = glfwCreateWindow(1280, 720, name.c_str(), nullptr, nullptr);
        if (s_Window == nullptr)
            return;
        glfwMakeContextCurrent(s_Window);
        glfwSwapInterval(1); // Enable vsync

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(s_Window, true);
        ImGui_ImplOpenGL3_Init(s_GLSL_VERSION.c_str());
    }

    void Window::UpdateWindow() {
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(s_Window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(s_ClearColor.x * s_ClearColor.w, s_ClearColor.y * s_ClearColor.w, s_ClearColor.z * s_ClearColor.w, s_ClearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
        glfwSwapBuffers(s_Window);
    }

    void Window::Shutdown() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(s_Window);
        glfwTerminate();
    }

    bool Window::IsOpen() {
        return !glfwWindowShouldClose(s_Window);
    }
}