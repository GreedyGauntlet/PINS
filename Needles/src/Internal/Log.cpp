#include "ndlpch.h"
#include "Log.h"

namespace Needles {
	std::shared_ptr<spdlog::sinks::ringbuffer_sink_mt> Log::s_Ringbuffer;
	std::shared_ptr<spdlog::logger> Log::s_Logger;

	void Log::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_Logger = spdlog::stdout_color_mt("NEEDLES");
		s_Logger->set_level(spdlog::level::trace);

		s_Ringbuffer = std::make_shared<spdlog::sinks::ringbuffer_sink_mt>(1000);
		s_Logger->sinks().push_back(s_Ringbuffer);
	}
}