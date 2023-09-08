#include "ndlpch.h"
#include "TestHandler.h"
#include "Testing/TestCase.h"
#include "Security/Encryption.h"

namespace Needles {

	void TestHandler::RunTests() {
		std::vector<TestCase> tests;
		static uint32_t passed = 0;
		static uint32_t failed = 0;
		static uint32_t warnings = 0;

		// ====================================== ENCRYPTION TESTS ======================================

		// testing generate seed
		tests.push_back(TestCase([]() {
			Seed seed = Encryption::GenerateSeed();

			if (seed.Size != 32 && seed.Size != 16 && seed.Size != 24) {
				NDL_ERROR("Seed did not have valid size\n\t\tExpected: 16, 24, or 32\n\t\tRecieved: " + std::to_string(seed.Size));
				failed++;
				return;
			}

			bool nonzero = false;
			for (uint8_t i = 0; i < seed.Size; i++)
				if (seed.Bytes[i] != 0)
					nonzero = true;
			if (!nonzero) {
				NDL_ERROR("Seed did not generate a valid non-zero seed");
				failed++;
				return;
			}

			NDL_INFO("Specified Seed test passed!");
			passed++;
		}));

		// testing set and get seed
		tests.push_back(TestCase([]() {
			Seed prior_seed = Encryption::GenerateSeed();
			Encryption::SetSeed(prior_seed);
			Seed post_seed = Encryption::GetSeed();
			
			bool verified = true;
			if (prior_seed.Size != post_seed.Size)
				verified = false;
			for (uint8_t i = 0; i < post_seed.Size; i++)
				if (post_seed.Bytes[i] != prior_seed.Bytes[i])
					verified = false;

			if (!verified) {
				NDL_ERROR("Generated seed was unable to be statically set");
				failed++;
				return;
			}

			NDL_INFO("Seed Get/Set test passed!");
			passed++;
		}));

		// test encrypting and decrypting
		tests.push_back(TestCase([]() {
			Seed seed = Encryption::GenerateSeed();
			Encryption::SetSeed(seed);

			Data data;
			data.Size = 16;
			uint8_t base_string[16] = "Hello, World!";
			uint8_t data_string[16] = "Hello, World!";
			data.Bytes = data_string;

			Encryption::Encrypt(data);
			bool encrypted = false;
			for (int i = 0; i < data.Size; i++)
				if (data.Bytes[i] != base_string[i])
					encrypted = true;
			if (!encrypted) {
				NDL_ERROR("Unable to properly encrypt data");
				failed++;
				return;
			}

			Encryption::Decrypt(data);
			bool decrypted = true;
			for (int i = 0; i < data.Size; i++)
				if (data.Bytes[i] != base_string[i])
					decrypted = false;
			if (!decrypted) {
				NDL_ERROR("Unable to properly decrypt data");
				failed++;
				return;
			}

			NDL_INFO("Encryption/Decryption test passed!");
			passed++;
		}));

		for (TestCase test : tests)
			test.Execute();

		std::cout << "\n=============== RESULTS =============== \n";
		NDL_TRACE("TESTS PASSED: " + std::to_string(passed) + "/" + std::to_string(tests.size()));
		NDL_TRACE("TESTS FAILED: " + std::to_string(failed) + "/" + std::to_string(tests.size()));
		NDL_TRACE("WARNINGS: " + std::to_string(warnings));
		std::cout << "======================================= \n";
	}
}