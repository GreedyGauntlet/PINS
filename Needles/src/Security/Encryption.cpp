#include "ndlpch.h"
#include "Encryption.h"
#include <cstdint>
#include <openssl/aes.h>
#include <openssl/rand.h>

namespace Needles {
	static Seed s_Seed;

	Seed& Encryption::GenerateSeed(uint8_t size) {
		Seed seed;

		// set randomized data
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(0, UINT8_MAX);
		seed.Bytes = new uint8_t[size];
		for (size_t i = 0; i < size; i++)
			seed.Bytes[i] = dis(gen);

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

	void Encryption::Encrypt(Data& data) {
		AES_KEY aesKey;
		AES_set_encrypt_key(seed.Bytes, seed.Size * 8, &aesKey);
		
		uint8_t iv[AES_BLOCK_SIZE];
		RAND_bytes(iv, AES_BLOCK_SIZE);
		data.IV = &iv;
		
		AES_cbc_encrypt(data.Bytes, data.Bytes, data.Size, &aesKey, data.IV, AES_ENCRYPT);
		data.Encrypted = true;
	}

	void Encryption::Decrypt(Data& data) {
		AES_KEY aesKey;
		AES_set_encrypt_key(seed.Bytes, seed.Size * 8, &aesKey);

		AES_cbc_encrypt(data.Bytes, data.Bytes, data.Size, &aesKey, data.IV, AES_DECRYPT);
		data.Encrypted = false;
	}
}
