#include "ndlpch.h"
#include "TestHandler.h"
#include "Testing/TestCase.h"

namespace Needles {
	static std::vector<TestCase> s_Tests;

	void TestHandler::AddTest(TestCase tc) {
		s_Tests.push_back(tc);
	}

	void TestHandler::AddTest(std::string name, std::function<bool()> test) {
		TestCase tc = TestCase(name, test);
		AddTest(tc);
	}

	void TestHandler::ClearTests() {
		s_Tests.clear();
	}

	TestResults& TestHandler::RunTests(bool log) {
		TestResults results;

		for (TestCase test : s_Tests) {
			bool result = test.Execute();
			if (result) {
				NDL_INFO("{} passed!", test.GetName());
				results.Passed++;
			} else NDL_ERROR("{} failed!", test.GetName());
			results.Total++;
		}

		if (log) {
			std::cout << "\n=============== RESULTS =============== \n";
			NDL_TRACE("TESTS PASSED: " + std::to_string(results.Passed) + "/" + std::to_string(results.Total));
			std::cout << "======================================= \n";
		}
		return results;
	}
}