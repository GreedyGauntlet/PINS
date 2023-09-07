#pragma once

namespace Needles {
	class TestCase {
	public:
		TestCase(std::function<void()> test);
		void Execute();
	private:
		std::function<void()> m_Test;
	};
}