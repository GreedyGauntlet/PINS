#include "ndlpch.h"
#include "Testing/TestHandler.h"

int main() {
	Needles::Log::Init();
	Needles::TestHandler::RunTests();
	return 0;
}