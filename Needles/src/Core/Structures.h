#pragma once
#define SEED_SIZE 32
#define MAX_TCP_PACKET_SIZE 1460
#define MAX_UDP_PACKET_SIZE 1500
#define AUTH_KEY_SIZE 256
#define UID_SIZE 512

namespace Needles {
	struct IPAddress {
		uint8_t IPv4[4] = { 0 };
		uint8_t IPv6[16] = { 0 };
	};

	enum class PacketType {
		TCP = 0,
		UDP = 1
	};

	struct NetworkAddress {
		IPAddress IP = { 0 };
		uint16_t Port = 0;
	};

	struct PacketConfig {
		bool Guest = true;
		PacketType Type = PacketType::TCP;
		uint8_t UID[UID_SIZE] = { 0 };
		uint8_t Authentication[AUTH_KEY_SIZE] = { 0 };
	};

	struct Socket {
		int Address = 0;
		bool Open = false;
	};

	struct ServerConfig {
		uint16_t Port = 0;
		int MaxClients = 10;
		bool Active = false;
		Socket HostSocket = { 0 };
	};

	struct ClientConfig {
		uint8_t UID[UID_SIZE] = { 0 };
		uint8_t Authentication[AUTH_KEY_SIZE] = { 0 };
		NetworkAddress Connection = { 0 };
		bool Connected = false;
		Socket ConnectionSocket = { 0 };
	};

	struct Seed {
		uint8_t* Bytes = nullptr;
		uint8_t Size = SEED_SIZE;
	};

	struct Data {
		uint8_t* Bytes = nullptr;
		size_t Size = 0;
		bool Encrypted = false;
#ifdef OPENSSL_READY
		uint8_t* IV = nullptr;
#endif
	};

}