#include "Core/Application.h"

int main(int, char**) {
    if (PINS::Application::Initialize()) {
        PINS::Application::Run();
        PINS::Application::Shutdown();
        return 0;
    }
    return 1;
}
