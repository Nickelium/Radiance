#pragma once

#include <spdlog/sinks/base_sink.h>
#include <imgui.h>

namespace Radiance
{

	template<typename Mutex>
	class ImGuiSink : public spdlog::sinks::base_sink <Mutex>
	{
	private:
		ImGuiTextBuffer m_Buffer;
		std::vector<int> m_LinesIndices;

	public:
		ImGuiTextBuffer& GetBuffer() { return m_Buffer; }
		std::vector<int>& GetLineIndices() { return m_LinesIndices; }
		void Clear() { flush_(); }
	protected:
		void sink_it_(const spdlog::details::log_msg& msg) override
		{
			// log_msg is a struct containing the log entry info like level, timestamp, thread id etc.
			// msg.raw contains pre formatted log

			// If needed (very likely but not mandatory), the sink formats the message before sending it to its final destination:
			fmt::memory_buffer formatted;
			spdlog::sinks::sink::formatter_->format(msg, formatted);
			std::string formattedString = fmt::to_string(formatted);

			int old_size = m_Buffer.size();
			m_Buffer.append(formattedString.c_str());
			for (int i = old_size, newSize = m_Buffer.size(); i < newSize; ++i)
				if (m_Buffer[i] == '\n')
					m_LinesIndices.push_back(i);

		}

		void flush_() override
		{
			m_Buffer.clear();
			m_LinesIndices.clear();
		}

	};

	#include <spdlog/details/null_mutex.h>
	using ImGuiSink_mt = ImGuiSink<std::mutex>;
	using ImGuiSink_st = ImGuiSink<spdlog::details::null_mutex>;
}