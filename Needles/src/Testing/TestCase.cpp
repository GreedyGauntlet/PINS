#include "ndlpch.h"
#include "TestCase.h"

namespace Needles {
	TestCase::TestCase(std::function<void()> test) 
		: m_Test(test) {
	}

	void TestCase::Execute() {
		m_Test();
	}
}