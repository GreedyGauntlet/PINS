#include "TestPanel.h"
#include "imgui.h"

namespace PINS {

    void TestPanel::Update() {
        ImGui::Begin("Hello, world!");
        ImGui::Text("This is some useful text.");
        ImGui::End();
    }

}