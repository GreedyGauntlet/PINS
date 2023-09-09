#pragma once
#define SEED_SIZE 32

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