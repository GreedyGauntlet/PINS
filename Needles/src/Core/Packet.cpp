#include "ndlpch.h"
#include "Packet.h"

namespace Needles {

	static void FlipBit(uint8_t& num, int pos) {
		num ^= (1 << pos);
	}

	Packet Packet::LoadPacket(uint8_t* bytes) {
		Packet packet = Packet();
		PacketConfig& config = packet.GetConfig();
		Data& data = packet.GetData();

		// size
		uint16_t size = bytes[0] | ((uint16_t)bytes[1] << 8);
		data.Size = size - 3 - UID_SIZE - AUTH_KEY_SIZE;

		// flags
		config.Guest = (bytes[2] & (1 << 0)) != 0;
		config.Type = (bytes[2] & (1 << 1)) != 0 ? PacketType::TCP : PacketType::UDP;
		data.Encrypted = (bytes[2] & (1 << 2)) != 0;

		// UID
		for (int i = 0; i < UID_SIZE; i++)
			config.UID[i] = bytes[i + 3];

		// AUTH
		for (int i = 0; i < AUTH_KEY_SIZE; i++)
			config.Authentication[i] = bytes[i + 3 + UID_SIZE];

		// DATA
		for (int i = 0; i < data.Size; i++)
			data.Bytes[i] = bytes[i + 3 + UID_SIZE + AUTH_KEY_SIZE];

		return packet;
	}

	Packet::Packet() {
		m_Data = { 0 };
		m_Config = { 0 };
	}

	Packet::Packet(Data& data) 
		: m_Data(data) {
		m_Config = { 0 };
	}

	Packet::Packet(Data& data, PacketConfig config)
		: m_Data(data), m_Config(config) {
	}

	uint16_t Packet::Size() {
		return m_Data.Size +
			   UID_SIZE +
			   AUTH_KEY_SIZE +
			   3;  // 3 per the packet structure, 2 is the packet size 1 is the packet flags
	}

	uint8_t* Packet::Bytes() { // NOTE: this is little endian
		uint16_t size = Size();
		uint8_t* bytes = new uint8_t[size];

		// size
		bytes[0] = (uint8_t)(size & 0xFF);
		bytes[1] = (uint8_t)((size >> 8) & 0xFF);

		// flags
		bytes[2] = 0;
		if (m_Config.Guest) FlipBit(bytes[2], 0);
		if (m_Config.Type == PacketType::TCP) FlipBit(bytes[2], 1);
		if (m_Data.Encrypted) FlipBit(bytes[2], 2);

		// UID
		for (int i = 0; i < UID_SIZE; i++)
			bytes[i + 3] = m_Config.UID[i];

		// AUTH
		for (int i = 0; i < AUTH_KEY_SIZE; i++)
			bytes[i + 3 + UID_SIZE] = m_Config.Authentication[i];

		// DATA
		for (int i = 0; i < m_Data.Size; i++)
			bytes[i + 3 + UID_SIZE + AUTH_KEY_SIZE] = m_Data.Bytes[i];

		return bytes;
	}

}