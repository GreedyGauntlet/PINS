#pragma once
#include <algorithm>
#define SEED_SIZE 32

namespace Needles {

	struct IPAddress {
		uint8_t IPv4[4] = { 0 };
		uint8_t IPv6[16] = { 0 };
	};

	struct NetworkAddress {
		IPAddress IP = { 0 };
		uint16_t Port = 0;
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