#pragma once
#include "Core/Structures.h"

#define MAX_TCP_PACKET_SIZE 1460
#define MAX_UDP_PACKET_SIZE 1500
#define AUTH_KEY_SIZE 256
#define UID_SIZE 512

namespace Needles {
	enum class PacketType {
		TCP = 0,
		UDP = 1
	};

	struct PacketConfig {
		bool Guest = true;
		PacketType Type = PacketType::TCP;
		uint8_t UID[UID_SIZE] = { 0 };
		uint8_t Authentication[AUTH_KEY_SIZE] = { 0 };
	};

	class Packet {
	public:
		static Packet LoadPacket(uint8_t* bytes);
	public:
		Packet();
		Packet(Data& data);
		Packet(Data& data, PacketConfig config);
		PacketConfig& GetConfig() { return m_Config; }
		Data& GetData() { return m_Data; }
		uint16_t Size();
		uint8_t* Bytes();
		bool IsValid() { return m_Config.Type == PacketType::TCP ? Size() <= MAX_TCP_PACKET_SIZE : Size() <= MAX_UDP_PACKET_SIZE; }
	private:
		PacketConfig m_Config;
		Data m_Data;
	};
}

//===================== PACKET STRUCTURE ======================
// | 2 bytes: packet size | 1 byte: [isGuest, isTCP, isEncrypted, 0, 0, 0, 0, 0] | UID_SIZE bytes: UID | AUTH_KEY_SIZE bytes: Authentication | Data size bytes: Data.Bytes |