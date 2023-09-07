#include "ndlpch.h"
#include "Encryption.h"
#include <chrono>
#include <cstdint>

namespace Needles {
	static Seed s_Seed;

	Seed& Encryption::GenerateSeed(uint8_t size) {
		Seed seed;

		// set epoch time
		auto now = std::chrono::system_clock::now();
		std::chrono::duration<double> duration = now.time_since_epoch();
		seed.Epoch = std::chrono::duration_cast<std::chrono::seconds>(duration).count();

		// set randomized data
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(0, UINT8_MAX);
		seed.Data = new uint8_t[size];
		for (size_t i = 0; i < size; i++)
			seed.Data[i] = dis(gen);

		// set size
		seed.Size = size;

		return seed;
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