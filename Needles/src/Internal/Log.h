#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/ringbuffer_sink.h"
#include "spdlog/fmt/ostr.h"

namespace Needles {
	class Log {
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
		inline static std::shared_ptr<spdlog::sinks::ringbuffer_sink_mt>& GetRingBuffer() { return s_Ringbuffer; }
	private:
		static std::shared_ptr<spdlog::sinks::ringbuffer_sink_mt> s_Ringbuffer;
		static std::shared_ptr<spdlog::logger> s_Logger;
	};
}

//Core log macros
#define NDL_ERROR(...)   ::Needles::Log::GetLogger()->error(__VA_ARGS__)
#define NDL_WARN(...)    ::Needles::Log::GetLogger()->warn(__VA_ARGS__)
#define NDL_INFO(...)    ::Needles::Log::GetLogger()->info(__VA_ARGS__)
#define NDL_TRACE(...)   ::Needles::Log::GetLogger()->trace(__VA_ARGS__)
#define NDL_FATAL(...)   ::Needles::Log::GetLogger()->fatal(__VA_ARGS__)
#define NDL_ASSERT(x, ...) { if(!(x)) {NDL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}