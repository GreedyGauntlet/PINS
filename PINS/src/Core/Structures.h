#pragma once
#include <vector>
#include <string>

namespace PINS {
    struct ClientNode {
        std::vector<ClientNode*> Subclients;
        std::string Name;
        ClientNode(std::string name) { Name = name; }
    };
}