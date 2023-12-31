#include "ndlpch.h"
#include "Encryption.h"
#include <cstdint>

#ifdef OPENSSL_READY
	#include <openssl/aes.h>
	#include <openssl/rand.h>
#endif

namespace Needles {
	static Seed s_Seed;

	Seed& Encryption::GenerateSeed() {
		Seed seed;

		// set randomized data
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(0, UINT8_MAX);
		seed.Bytes = new uint8_t[SEED_SIZE];
		for (size_t i = 0; i < SEED_SIZE; i++)
			seed.Bytes[i] = dis(gen);

		return seed;
	}

	Seed& Encryption::GetSeed() {
		return s_Seed;
	}

	void Encryption::SetSeed(Seed& seed) {
		s_Seed = seed;
	}

	void Encryption::Encrypt(Data& data) { // TODO: this is a weak encrypt, use openSSL's AES algorithm later
		if (data.Encrypted) return;
		for (size_t i = 0; i < data.Size; i++)
			data.Bytes[i] ^= s_Seed.Bytes[i % s_Seed.Size];
		data.Encrypted = true;
	}

	void Encryption::Decrypt(Data& data) {
		if (!data.Encrypted) return;
		for (size_t i = 0; i < data.Size; i++)
			data.Bytes[i] ^= s_Seed.Bytes[i % s_Seed.Size];
		data.Encrypted = false;
	}

	#ifdef OPENSSL_READY
	void Encryption::Encrypt(Data& data) { //TODO: note that IV will be used and need to be added to packet size calculation when AES is implemented
		AES_KEY aesKey;
		AES_set_encrypt_key(s_Seed.Bytes, s_Seed.Size * 8, &aesKey);
		
		uint8_t iv[AES_BLOCK_SIZE];
		RAND_bytes(iv, AES_BLOCK_SIZE);
		data.IV = iv;
		
		AES_cbc_encrypt(data.Bytes, data.Bytes, 16, &aesKey, data.IV, AES_ENCRYPT);
		data.Encrypted = true;
	}

	void Encryption::Decrypt(Data& data) {
		AES_KEY aesKey;
		AES_set_encrypt_key(s_Seed.Bytes, s_Seed.Size * 8, &aesKey);

		AES_cbc_encrypt(data.Bytes, data.Bytes, data.Size, &aesKey, data.IV, AES_DECRYPT);
		data.Encrypted = false;
	}
	#endif
}
