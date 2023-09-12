#include "ndlpch.h"
#include "Client.h"

namespace Needles {

	Client::Client(ClientConfig config)
		: m_Config(config) {
	}

	bool Client::Connect(const NetworkAddress& destination) {
		// make sure we are open to connect
		if (m_Config.Connected) {
			NDL_ERROR("Client is already registered as connected. Please disconnect before attempting a new connection.");
			return false;
		}

		// make sure network is initialized
		NetworkUtils::SoftInitialize();

		// validate port
		if (destination.Port <= 1024)
			NDL_WARN("Destination port is either invalid or reserved; connection is likely to fail");

		// create socket
		m_Config.ConnectionSocket = NetworkUtils::CreateSocket();

		// attempt connection
		m_Config.Connected = NetworkUtils::ConnectSocket(m_Config.ConnectionSocket, destination);

		return IsConnected();
	}

	void Client::Disconnect() {
		NetworkUtils::CloseSocket(m_Config.ConnectionSocket);
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
		return m_Config.Connected;
	}

}