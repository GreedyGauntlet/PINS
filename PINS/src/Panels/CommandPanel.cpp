#include "CommandPanel.h"
#include "imgui.h"
#include <iostream>
#include <iomanip>
#include <ctime>

namespace PINS {

    static std::string GetTimeStamp() {
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);
        std::string hour = (now->tm_hour < 10) ? "0" + std::to_string(now->tm_hour) : std::to_string(now->tm_hour);
        std::string min = (now->tm_min < 10) ? "0" + std::to_string(now->tm_min) : std::to_string(now->tm_min);
        std::string sec = (now->tm_sec < 10) ? "0" + std::to_string(now->tm_sec) : std::to_string(now->tm_sec);
        std::string timestamp = "[" + hour + ":" + min + ":" + sec + "]";
        return timestamp;
    }

    void CommandPanel::Update() {
        ImGui::Begin("Server Commands");

        ImVec2 contentRegionMax = ImGui::GetWindowContentRegionMax();
		ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
		float remainingHeight = contentRegionAvailable.y;
		float inputHeight = ImGui::GetFrameHeight();
		remainingHeight -= inputHeight + ImGui::GetStyle().ItemSpacing.y;

		ImGui::BeginChild("MainContent", ImVec2(contentRegionAvailable.x, remainingHeight), false);
		for (auto cmd : m_Commands) {
            switch (cmd.State) {
                case CommandState::Rejected:
                    ImGui::PushStyleColor(ImGuiCol_Text, {1.0f, 0.2f, 0.3f, 1.0f});
                    break;
                case CommandState::Resolved:
                    ImGui::PushStyleColor(ImGuiCol_Text, {0.1f, 1.0f, 0.3f, 1.0f});
                    break;
                case CommandState::Pending:
                    ImGui::PushStyleColor(ImGuiCol_Text, {1.0f, 0.8f, 0.05f, 1.0f});
                    break;
                default:
                    ImGui::PushStyleColor(ImGuiCol_Text, {1.0f, 1.0f, 1.0f, 1.0f});
            }

			ImGui::Text((cmd.Timestamp + ": " + cmd.CommandString).c_str());

			ImGui::PopStyleColor();
		}
		ImGui::EndChild();

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetStyle().ItemSpacing.y);

		static char inputCommand[1024] = "";
		ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionMax().x);
		static bool enterPressed = false;
		if (enterPressed) {
			ImGui::SetKeyboardFocusHere();
			enterPressed = false;
		}
		enterPressed = ImGui::InputText("##Input", inputCommand, 512, ImGuiInputTextFlags_EnterReturnsTrue);
		if (enterPressed) {
            Command cmd;
            cmd.CommandString = std::string(inputCommand);
            cmd.Timestamp = GetTimeStamp();
            m_Commands.push_back(cmd);
			inputCommand[0] = '\0';
		}

        ImGui::End();
    }

}