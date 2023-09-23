#include "ClientDetailsPanel.h"
#include "imgui.h"
#include <iostream>

namespace PINS {

    static std::vector<ClientNode*> s_OpenClients;
    static ClientNode* s_SelectedClient;

    ClientDetailsPanel::ClientDetailsPanel() {
    }

    void ClientDetailsPanel::Update() {
        ImGui::Begin("Client Details");

        if (ImGui::BeginTabBar("Clients")) {

            for (auto client : s_OpenClients) {
                ImGuiTabItemFlags flags = ImGuiTabBarFlags_None;
                if (client == s_SelectedClient)  {
                    flags = ImGuiTabItemFlags_SetSelected;
                    s_SelectedClient = nullptr;
                }

                if (ImGui::BeginTabItem(client->Name.c_str(), NULL, flags)) {
                    ImGui::Text("Cameron gotta finish up needles before this is implemented");
                    ImGui::EndTabItem();
                }
            }

            ImGui::EndTabBar();
        }
        ImGui::End();
    }

    void ClientDetailsPanel::OpenClient(ClientNode* client) {
        s_SelectedClient = client;
        for (auto i_client : s_OpenClients)
            if (client == i_client) return;
        s_OpenClients.push_back(client);
    }

}