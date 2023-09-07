#pragma once
#define DEFAULT_SEED_SIZE 255

namespace Needles {
	struct Seed {
		uint64_t Epoch;
		uint8_t* Data;
		uint8_t Size;
	};

	struct Data {
		uint8_t* Data;
		uint8_t Size;
	};

	class Encryption {
	public:
		static Seed& GenerateSeed(uint8_t size = DEFAULT_SEED_SIZE);
		static Seed& GetSeed();
		static void SetSeed(Seed& seed);
		static Data& Encrypt(Data& data);
		static Data& Decrypt(Data& data);
	};
}