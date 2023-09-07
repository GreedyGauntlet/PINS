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

		// testing default generate seed
		tests.push_back(TestCase([]() {
			Seed default_seed = Encryption::GenerateSeed();

			if (default_seed.Size != DEFAULT_SEED_SIZE) {
				Error("Default seed did not default to defined size\n\t\tExpected: " + std::to_string(DEFAULT_SEED_SIZE) + "\n\t\tRecieved: " + std::to_string(default_seed.Size));
				failed++;
				return;
			}

			bool nonzero = false;
			for (uint8_t i = 0; i < default_seed.Size; i++)
				if (default_seed.Data[i] != 0)
					nonzero = true;
			if (!nonzero) {
				Error("Default seed did not generate a valid non-zero seed");
				failed++;
				return;
			}

			if (default_seed.Epoch == 0) {
				Error("Default seed epoch is zero");
				failed++;
				return;
			}

			Info("Default seed test passed!");
			passed++;
		}));

		// testing specific generate seed
		tests.push_back(TestCase([]() {
			std::random_device rd;
			std::mt19937 gen(rd()); 
			std::uniform_int_distribution<int> dis(1, UINT8_MAX);
			uint8_t random_size = dis(gen);

			Seed spec_seed = Encryption::GenerateSeed(random_size);

			if (spec_seed.Size != random_size) {
				Error("Seed did not have defined size\n\t\tExpected: " + std::to_string(random_size) + "\n\t\tRecieved: " + std::to_string(spec_seed.Size));
				failed++;
				return;
			}

			bool nonzero = false;
			for (uint8_t i = 0; i < spec_seed.Size; i++)
				if (spec_seed.Data[i] != 0)
					nonzero = true;
			if (!nonzero) {
				Error("Seed did not generate a valid non-zero seed");
				failed++;
				return;
			}

			if (spec_seed.Epoch == 0) {
				Error("Seed epoch is zero");
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
			else if (prior_seed.Epoch != post_seed.Epoch)
				verified = false;
			for (uint8_t i = 0; i < post_seed.Size; i++)
				if (post_seed.Data[i] != prior_seed.Data[i])
					verified = false;

			if (!verified) {
				Error("Generated seed was unable to be statically set");
				failed++;
				return;
			}

			Info("Seed Get/Set test passed!");
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