#pragma once
#include "Packet.h"

namespace Needles {
	struct ClientConfig {
		uint8_t UID[UID_SIZE] = { 0 };
		uint8_t Authentication[AUTH_KEY_SIZE] = { 0 };
		NetworkAddress Connection = { 0 };
	};

	class Client {
	public:
		Client(ClientConfig config = { 0 });
		void Connect(const NetworkAddress& destination);
		void Disconnect();
		bool Send(Packet packet);
		bool Recieve();
		bool IsConnected();
		ClientConfig& GetConfig() { return m_Config; }
	private:
		ClientConfig m_Config;
	};
}