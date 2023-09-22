#pragma once

namespace PINS {
    class Application {
    public:
        static bool Initialize();
        static void Run();
        static void Shutdown();
    };
}