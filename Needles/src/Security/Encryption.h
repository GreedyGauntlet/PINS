#pragma once
#include "Core/Structures.h"

namespace Needles {
	class Encryption {
	public:
		static Seed& GenerateSeed();
		static Seed& GetSeed();
		static void SetSeed(Seed& seed);
		static void Encrypt(Data& data);
		static void Decrypt(Data& data);
	};
}
