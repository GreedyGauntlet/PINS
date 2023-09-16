#pragma once
#include "Core/Structures.h"

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

namespace Needles {
	class NetworkUtils {
	public:
#ifdef _WIN32  // functions only needed for Windows Sockets
		static void Initialize();
		static void SoftInitialize();
		static bool IsInitialized();
#endif
		static bool ConnectSocket(const Socket& socket, const NetworkAddress& destination);
		static bool Listen(const ServerConfig& config);
		static Socket& AcceptConnection(const ServerConfig& config);
		static Socket& CreateSocket();
		static void CloseSocket(Socket& socket);
		static void Shutdown();
		static std::string IPv4String(const NetworkAddress& address);
		static std::string IPv6String(const NetworkAddress& address);
	};
}
