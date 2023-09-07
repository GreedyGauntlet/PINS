#include "ndlpch.h"
#include "TestHandler.h"
#include "Testing/TestCase.h"

namespace Needles {
	void TestHandler::RunTests() {
		std::vector<TestCase> tests;

		tests.push_back(TestCase([]() {
			std::cout << "Test protocol loaded\n";
		}));

		tests.push_back(TestCase([]() {
			// put test functionality here
		}));

		for (TestCase test : tests)
			test.Execute();
	}
}