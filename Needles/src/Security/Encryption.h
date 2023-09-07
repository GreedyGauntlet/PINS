#pragma once
#define SEED_SIZE 32

namespace Needles {
	struct Seed {
		uint8_t* Bytes = nullptr;
		uint8_t Size = SEED_SIZE;
	};

	struct Data {
		uint8_t* Bytes = nullptr;
		uint8_t Size = 0;
		uint8_t* IV = nullptr;
		bool Encrypted = false;
	};

	class Encryption {
	public:
		static Seed& GenerateSeed();
		static Seed& GetSeed();
		static void SetSeed(Seed& seed);
		static void Encrypt(Data& data);
		static void Decrypt(Data& data);
	};
}
