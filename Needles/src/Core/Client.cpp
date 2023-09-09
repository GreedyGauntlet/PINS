#include "ndlpch.h"
#include "Client.h"

namespace Needles {

	Client::Client(ClientConfig config)
		: m_Config(config) {
	}

	void Client::Connect(const NetworkAddress& destination) {
		// TODO
	}

	void Client::Disconnect() {
		// TODO
	}

	bool Client::Send(Packet packet) {
		// TODO
		return false;
	}

	bool Client::Recieve() {
		// TODO
		return false;
	}

	bool Client::IsConnected() {
		// TODO
		return false;
	}

}