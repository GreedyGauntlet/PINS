#include "ndlpch.h"
#include "TestHandler.h"
#include "Testing/TestCase.h"
#include "Security/Encryption.h"

#define RED_TEXT "\x1b[31m"
#define GREEN_TEXT "\x1b[32m"
#define YELLOW_TEXT "\x1b[33m"
#define RESET_COLOR "\x1b[0m"

namespace Needles {
	static void Error(std::string error) {
		std::cout << RED_TEXT << "[ERROR]: " + error << RESET_COLOR << std::endl;
	}

	static void Trace(std::string trace) {
		std::cout << RESET_COLOR << "[TRACE]: " + trace << RESET_COLOR << std::endl;
	}

	static void Info(std::string info) {
		std::cout << GREEN_TEXT << "[INFO]: " + info << RESET_COLOR << std::endl;
	}

	static void Warn(std::string warn) {
		std::cout << YELLOW_TEXT << "[WARN]: " + warn << RESET_COLOR << std::endl;
	}

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
				Error("Seed did not have valid size\n\t\tExpected: 16, 24, or 32\n\t\tRecieved: " + std::to_string(seed.Size));
				failed++;
				return;
			}

			bool nonzero = false;
			for (uint8_t i = 0; i < seed.Size; i++)
				if (seed.Bytes[i] != 0)
					nonzero = true;
			if (!nonzero) {
				Error("Seed did not generate a valid non-zero seed");
				failed++;
				return;
			}

			Info("Specified Seed test passed!");
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
				Error("Generated seed was unable to be statically set");
				failed++;
				return;
			}

			Info("Seed Get/Set test passed!");
			passed++;
		}));

		// test encrypting and decrypting
		tests.push_back(TestCase([]() {
			Seed seed = Encryption::GenerateSeed();
			Encryption::SetSeed(seed);

			Data data;
			data.Size = 4;
			uint8_t string[16] = "Hello, World!";
			data.Bytes = string;

			Encryption::Encrypt(data);

			Info("Encryption/Decryption test passed!");
			passed++;
		}));

		for (TestCase test : tests)
			test.Execute();

		std::cout << "\n=============== RESULTS =============== \n";
		Trace("TESTS PASSED: " + std::to_string(passed) + "/" + std::to_string(tests.size()));
		Trace("TESTS FAILED: " + std::to_string(failed) + "/" + std::to_string(tests.size()));
		Trace("WARNINGS: " + std::to_string(warnings));
		std::cout << "======================================= \n";
	}
}