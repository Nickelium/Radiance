#pragma once
#pragma warning(push)
#pragma warning(disable:26495)
#pragma warning(disable:26451)
#pragma warning(disable:26498)
#pragma warning(disable:6387)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

#include "Radiance/ImGui/ImGuiSink.h"

#include "Singleton.h"

namespace Radiance
{
	class Logger : public Singleton<Logger>
	{
	public:
		Logger();
		inline std::shared_ptr<spdlog::logger>& GetCoreLogger()
		{ return m_CoreLogger; }
		inline std::shared_ptr<spdlog::logger>& GetClientLogger() 
		{ return m_ClientLogger; } 
		inline std::shared_ptr<ImGuiSink_mt>& GetSink()
		{ return m_ImGuiSink; }

	private:
		void Init();
		std::shared_ptr<spdlog::logger> m_CoreLogger;
		std::vector<spdlog::sink_ptr> m_CoreSinks;
		
		std::shared_ptr<spdlog::logger> m_ClientLogger;
		std::vector<spdlog::sink_ptr> m_ClientSinks;

		std::shared_ptr<ImGuiSink_mt> m_ImGuiSink;
	};
}

#define IMGUILOGGER ::Radiance::Logger::GetInstance().GetSink()

#ifdef RAD_DEBUG
// Core log macros
#define RAD_CORE_TRACE(...)    ::Radiance::Logger::GetInstance().GetCoreLogger()->trace(__VA_ARGS__)
#define RAD_CORE_INFO(...)     ::Radiance::Logger::GetInstance().GetCoreLogger()->info(__VA_ARGS__)
#define RAD_CORE_WARN(...)     ::Radiance::Logger::GetInstance().GetCoreLogger()->warn(__VA_ARGS__)
#define RAD_CORE_ERROR(...)    ::Radiance::Logger::GetInstance().GetCoreLogger()->error(__VA_ARGS__)
#define RAD_CORE_FATAL(...)    ::Radiance::Logger::GetInstance().GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define RAD_TRACE(...)		 ::Radiance::Logger::GetInstance().GetClientLogger()->trace(__VA_ARGS__)
#define RAD_INFO(...)		 ::Radiance::Logger::GetInstance().GetClientLogger()->info(__VA_ARGS__)
#define RAD_WARN(...)		 ::Radiance::Logger::GetInstance().GetClientLogger()->warn(__VA_ARGS__)
#define RAD_ERROR(...)		 ::Radiance::Logger::GetInstance().GetClientLogger()->error(__VA_ARGS__)
#define RAD_FATAL(...)		 ::Radiance::Logger::GetInstance().GetClientLogger()->critical(__VA_ARGS__) 

#else

#define RAD_CORE_TRACE(...)
#define RAD_CORE_INFO(...)
#define RAD_CORE_WARN(...)
#define RAD_CORE_ERROR(...)
#define RAD_CORE_FATAL(...)

// Client log macros
#define RAD_TRACE(...)	
#define RAD_INFO(...)
#define RAD_WARN(...)	
#define RAD_ERROR(...)	
#define RAD_FATAL(...)	

#endif