#include "ClientHierarchyPanel.h"
#include "ClientDetailsPanel.h"
#include "imgui.h"

namespace PINS {

    ClientHierarchyPanel::ClientHierarchyPanel() {
        ClientNode* prigroup = new ClientNode("Priority Clients");
        ClientNode* plegroup = new ClientNode("Plebian Clients");
        prigroup->Subclients.push_back(new ClientNode("Jason VIP"));
        prigroup->Subclients.push_back(new ClientNode("Cameron VIP"));
        prigroup->Subclients.push_back(new ClientNode("Barack Obama"));
        prigroup->Subclients.push_back(new ClientNode("Michelle Obama"));
        plegroup->Subclients.push_back(new ClientNode("Pissmonger56"));
        plegroup->Subclients.push_back(new ClientNode("taxevader99"));
        plegroup->Subclients.push_back(new ClientNode("bartholemewbigshot08"));
        m_Clients.push_back(prigroup);
        m_Clients.push_back(plegroup);
    }

    void ClientHierarchyPanel::Update() {
        ImGui::Begin("Client Hierarchy");
        for (auto client : m_Clients)
           DrawClientNode(client);
        ImGui::End();
    }

    void ClientHierarchyPanel::DrawClientNode(ClientNode* client) {
        bool isGroup = client->Subclients.size() != 0;

        ImGuiTreeNodeFlags flags = ((m_SelectedClient == client) ? ImGuiTreeNodeFlags_Selected : 0)
        | ImGuiTreeNodeFlags_OpenOnArrow
        | ImGuiTreeNodeFlags_DefaultOpen
        | ImGuiTreeNodeFlags_SpanAvailWidth;

        bool opened = ImGui::TreeNodeEx((void*)client, flags, client->Name.c_str());

        if (ImGui::IsItemClicked()) 
			m_SelectedClient = client;
            
        if (opened) {
			if (isGroup) {
				for (auto subclient : client->Subclients)
				    DrawClientNode(subclient);
			}

            if (ImGui::IsItemClicked(ImGuiMouseButton_Left) && 
                ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) &&
                !isGroup) {
                ClientDetailsPanel::OpenClient(client);
            }

			ImGui::TreePop();
        }
    }

}