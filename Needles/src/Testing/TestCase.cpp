#include "ndlpch.h"
#include "TestCase.h"

namespace Needles {
	TestCase::TestCase(std::string name, std::function<bool()> test) 
		: m_Name(name), m_Test(test) {
	}

	bool TestCase::Execute() {
		return m_Test();
	}
}