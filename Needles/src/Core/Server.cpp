#include "ndlpch.h"
#include "Server.h"

namespace Needles {
    Server::Server(ServerConfig config) 
        : m_Config(config) {
    }

    bool Server::Open(uint16_t port) {
        // ensure the server is good to open
        if (m_Config.Active) {
            NDL_ERROR("Server is already being hosted on a connection. Please close the connection before attempting to open again.");
            return false;
        }

        // Make sure network is initialized
        NetworkUtils::SoftInitialize();

        // think about if port is valid or not
        m_Config.Port = port;
        if (m_Config.Port <= 1024)
            NDL_WARN("Indicated port is either invalid or reserved. Open is likely to fail.");

        // get socket
        m_Config.HostSocket = NetworkUtils::CreateSocket();

        // open host connection
        m_Config.Active = NetworkUtils::Listen(m_Config);

        // create handle clients thread
        std::thread(&Server::HandleClients, this).detach();

        return m_Config.Active;
    }

    void Server::Close() {
        // TODO: 
        // close socket and connection
        // stop handle clients thread
        // dont forget to close client sockets as well
    }

    void Server::HandleClients() {
        while (true) {
            ServerConfig conf = { 0 };
            Socket clientSocket = NetworkUtils::AcceptConnection(conf);

            if (clientSocket.Address != -1) {
                NDL_INFO("Connection accepted");
            } 
        }
    }

    void Server::ManageClient() {
        //TODO
    }

    bool Server::Send(Client client, Packet packet) {
        //TODO
        return false;
    }

    bool Server::Recieve(Client client) {
        //TODO
        return false;
    }
}