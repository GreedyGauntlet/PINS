#include "ndlpch.h"
#include "NetworkUtils.h"

namespace Needles {
	bool s_NetworkInitialized = false;

	void NetworkUtils::Initialize() {
        // initialize windows socket library
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            NDL_ASSERT(false, "WSAStartup failed.");
        }
        else if (LOBYTE(wsaData.wVersion) != 2 ||
            HIBYTE(wsaData.wVersion) != 2) {
            WSACleanup();
            NDL_ASSERT(false, "ERROR: Version 2.2 of Winsock is not available.");
        }
        else s_NetworkInitialized = true;
	}

    void NetworkUtils::SoftInitialize() {
        if (!s_NetworkInitialized)
            Initialize();
    }

	bool NetworkUtils::IsInitialized() {
		return s_NetworkInitialized;
	}

    bool NetworkUtils::ConnectSocket(const Socket& socket, const NetworkAddress& destination) {
        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(destination.Port);
        serverAddress.sin_addr.s_addr = inet_addr(IPv4String(destination).c_str()); // Replace with the server's IP address
        if (connect(socket.Address, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
            NDL_ERROR("Failed to connect to destination host");
            return false;
        }
        return true;
    }

    bool NetworkUtils::Listen(const ServerConfig& config) {
        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(config.Port); // Port number
        serverAddress.sin_addr.s_addr = INADDR_ANY; // Listen on any interface

        if (bind(config.HostSocket.Address, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
            NDL_ERROR("Unable to bind socket to port");
            return false;
        }

        // Start listening for connections
        if (listen(config.HostSocket.Address, config.MaxClients) == -1) {
            NDL_ERROR("Unable to listen for connections");
            return false;
        }
    }

    Socket& NetworkUtils::AcceptConnection(const ServerConfig& config) {
        Socket clientSocket;
        sockaddr_in clientAddress;
        int clientAddressSize = sizeof(clientAddress);
        clientSocket.Address = accept(config.HostSocket.Address, (struct sockaddr*)&clientAddress, &clientAddressSize);
        return clientSocket;
    }

    Socket& NetworkUtils::CreateSocket() {
        Socket mySocket;
        if ((mySocket.Address = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            NDL_ASSERT(false, "ERROR: Socket creation error");
        u_long mode = 1;
        ioctlsocket(mySocket.Address, FIONBIO, &mode);
        mySocket.Open = true;
        return mySocket;
    }

    void NetworkUtils::CloseSocket(Socket& socket) {
        shutdown(socket.Address, 0);
        closesocket(socket.Address);
        socket.Open = false;
    }

    void NetworkUtils::Shutdown() {
        if (IsInitialized())
            WSACleanup();
        s_NetworkInitialized = false;
    }

    std::string NetworkUtils::IPv4String(const NetworkAddress& address) {
        std::string str = "";
        for (int i = 0; i < 3; i++)
            str += std::to_string(address.IP.IPv4[i]) + ".";
        str += std::to_string(address.IP.IPv4[3]);
        return str;
    }

    std::string NetworkUtils::IPv6String(const NetworkAddress& address) {
        NDL_ASSERT(false, "Not implemented yet");
        return "";
    }
}