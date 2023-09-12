#pragma once
#include "Packet.h"
#include "Utils/NetworkUtils.h"

namespace Needles {
	class Client {
	public:
		Client(ClientConfig config = { 0 });
		bool Connect(const NetworkAddress& destination);
		void Disconnect();
		bool Send(Packet packet);
		bool Recieve();
		bool IsConnected();
		ClientConfig& GetConfig() { return m_Config; }
	private:
		ClientConfig m_Config;
	};
}