#pragma once
#include "Panel.h"
#include "../Core/Structures.h"

namespace PINS {
    class ClientDetailsPanel : public Panel {
    public:
        ClientDetailsPanel();
        virtual void Initialize() override {};
        virtual void Update() override;
        static void OpenClient(ClientNode* client);
    };
}