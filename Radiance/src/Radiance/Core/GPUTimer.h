#pragma once

#include "Time.h"

namespace Radiance
{
	class GPUTimer
	{
	public:
		using QueryCallback = std::function<void(ProfileResult)>;

		virtual ~GPUTimer() = default;
		virtual void Update() = 0;
		virtual void Begin(const char* _name, const QueryCallback& _callback) = 0;
		virtual void End(const char* _name) = 0;
	};
}

#define GPUPROFILE_BEGIN(NAME) m_Application->GetGPUTimer()->Begin(#NAME, [&](Radiance::ProfileResult _profileResult) {m_ProfileResults.push_back(_profileResult);} )

#define GPUPROFILE_END(NAME) m_Application->GetGPUTimer()->End(#NAME)