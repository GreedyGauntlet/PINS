#include "ndlpch.h"
#include "Encryption.h"

namespace Needles {
	static Seed s_Seed;

	Seed& Encryption::GenerateSeed() {
		// TODO
		return s_Seed;
	}

	Seed& Encryption::GetSeed() {
		return s_Seed;
	}

	void Encryption::SetSeed(Seed& seed) {
		s_Seed = seed;
	}

	Data& Encryption::Encrypt(Data& data) {
		// TODO
		return data;
	}

	Data& Encryption::Decrypt(Data& data) {
		// TODO
		return data;
	}
}