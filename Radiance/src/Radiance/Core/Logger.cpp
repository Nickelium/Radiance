#include "pch.h"
#include "Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Radiance
{
	Logger::Logger()
	{
		Init();
	}

	void Logger::Init()
	{
		m_ClientSinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		m_ClientSinks.push_back(m_ImGuiSink = std::make_shared<ImGuiSink_mt>());
		m_ClientLogger = std::make_shared<spdlog::logger>("CLI", begin(m_ClientSinks), end(m_ClientSinks));
		m_ClientLogger->set_level(spdlog::level::trace);
		m_ClientLogger->set_pattern("%^[%T] %n: %v%$");
		spdlog::register_logger(m_ClientLogger);

		m_CoreSinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		m_CoreSinks.push_back(m_ImGuiSink);
		m_CoreLogger = std::make_shared<spdlog::logger>("CORE", begin(m_CoreSinks), end(m_CoreSinks));
		m_CoreLogger->set_level(spdlog::level::trace);
		m_CoreLogger->set_pattern("%^[%T] %n: %v%$");
		spdlog::register_logger(m_CoreLogger);
	}

}