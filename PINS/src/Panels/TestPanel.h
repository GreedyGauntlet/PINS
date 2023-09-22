#pragma once
#include "Panel.h"

namespace PINS {
    class TestPanel : public Panel {
    public:
        TestPanel() = default;
        virtual void Initialize() override {};
        virtual void Update() override;
    };
}