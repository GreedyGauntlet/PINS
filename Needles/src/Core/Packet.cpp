#include "ndlpch.h"
#include "Packet.h"

namespace Needles {

	Packet Packet::LoadPacket(uint8_t bytes, uint32_t size) {
		// TODO
		return Packet();
	}

	Packet::Packet() {
		m_Data = { 0 };
		m_Config = { 0 };
	}

	Packet::Packet(Data data) 
		: m_Data(data) {
		m_Config = { 0 };
	}

	Packet::Packet(Data data, PacketConfig config)
		: m_Data(data), m_Config(config) {
	}

	uint32_t Packet::Size() {
		return m_Data.Size +
			   UID_SIZE +
			   AUTH_KEY_SIZE +
			   1;
	}

	uint8_t* Packet::Bytes() {
		// TODO
		return nullptr;
	}

}