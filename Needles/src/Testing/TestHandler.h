#pragma once
#include "Testing/TestCase.h"

namespace Needles {
	struct TestResults {
		uint32_t Passed = 0;
		uint32_t Total = 0;
	};

	class TestHandler {
	public:
		static TestResults& RunTests(bool log = true);
		static void AddTest(TestCase tc);
		static void AddTest(std::string name, std::function<bool()> test);
		static void ClearTests();
	};
}