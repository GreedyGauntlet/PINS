#pragma once

namespace Needles {
	class TestCase {
	public:
		TestCase(std::string name, std::function<bool()> test);
		bool Execute();
		std::string GetName() { return m_Name; };
	private:
		std::function<bool()> m_Test;
		std::string m_Name;
	};
}