#pragma once
#define DEFAULT_SEED_SIZE 255

namespace Needles {
	struct Seed {
		uint8_t* Bytes = nullptr;
		uint8_t Size = 0;
	};

	struct Data {
		uint8_t* Bytes = nullptr;
		uint8_t Size = 0;
		uint8_t* IV = nullptr;
		bool Encrypted = false;
	};

	class Encryption {
	public:
		static Seed& GenerateSeed(uint8_t size = DEFAULT_SEED_SIZE);
		static Seed& GetSeed();
		static void SetSeed(Seed& seed);
		static void Encrypt(Data& data);
		static void Decrypt(Data& data);
	};
}
