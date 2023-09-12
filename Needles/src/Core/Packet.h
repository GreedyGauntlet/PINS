#pragma once
#include "Core/Structures.h"

namespace Needles {
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