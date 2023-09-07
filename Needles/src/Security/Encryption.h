#pragma once

namespace Needles {
	struct Seed {
		uint64_t Epoch;
		uint8_t* Data;
		uint64_t Size;
	};

	struct Data {
		uint8_t* Data;
		uint64_t Size;
	};

	class Encryption {
	public:
		static Seed& GenerateSeed();
		static Seed& GetSeed();
		static void SetSeed(Seed& seed);
		static Data& Encrypt(Data& data);
		static Data& Decrypt(Data& data);
	};
}