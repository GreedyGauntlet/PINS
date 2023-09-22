#pragma once
#include <string>

namespace PINS {
    class Window {
    public:
        static bool Initialize();
        static void CreateWindow(std::string name);
        static void UpdateWindow();
        static void Shutdown();
        static bool IsOpen();
    };
}