#pragma once
#include "Core/Structures.h"

namespace Needles {
	class NetworkUtils {
	public:
		static void Initialize();
		static void SoftInitialize();
		static bool IsInitialized();
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