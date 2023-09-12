#pragma once
#include "Core/Client.h"
#include "Utils/NetworkUtils.h"

namespace Needles {
    class Server{
    public:
        Server(ServerConfig config = { 0 });
        bool Open(uint16_t port);
        void Close();
        ServerConfig& GetConfig() { return m_Config; }
    private:
        void HandleClients();
        void ManageClient(); // for now, this is all for testing but eventually we want to take in scripts as a parameter and bind that to a client to modify it's behavior
        bool Send(Client client, Packet packet);
        bool Recieve(Client client);
    private:
        ServerConfig m_Config;
        std::vector<Client> m_Clients;
    };
}