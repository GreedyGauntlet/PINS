#pragma once
#include "Panel.h"
#include <vector>
#include <string>

namespace PINS {
    enum class CommandState {
        Pending = 0,
        Rejected = 1,
        Resolved = 2,
    };
    
    struct Command {
        std::string CommandString = "";
        std::string Timestamp = "";
        CommandState State = CommandState::Pending;
    };

    class CommandPanel : public Panel {
    public:
        CommandPanel() = default;
        virtual void Initialize() override {};
        virtual void Update() override;
    private:
        std::vector<Command> m_Commands;
    };
}