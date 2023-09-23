#pragma once
#include "Panel.h"
#include "../Core/Structures.h"

namespace PINS {
    class ClientHierarchyPanel : public Panel {
    public:
        ClientHierarchyPanel();
        virtual void Initialize() override {};
        virtual void Update() override;
    private:
        void DrawClientNode(ClientNode* client);
    private:
        std::vector<ClientNode*> m_Clients;
        ClientNode* m_SelectedClient;
    };
}