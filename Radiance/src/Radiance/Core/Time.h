#pragma once

#include <chrono>

namespace Radiance
{
	struct DataTime
	{
		float dt;
		float total;
	};

	class Timer
	{
	public:
		Timer();
		void Start();
		void Update();

		float GetDelta() const;
		float GetTotal() const;
		DataTime GetTimeStep() const;

		using Time = std::chrono::high_resolution_clock;
		using TimePoint = std::chrono::time_point<Time>;

		inline static TimePoint Now() { return Time::now();}
		inline static float Difference(const TimePoint& _t1, const TimePoint& _t2)
		{ return std::chrono::duration<float>(_t1 - _t2).count(); }

	private:
		TimePoint m_Current;
		TimePoint m_Start;
		TimePoint m_Last;

		float m_Dt;
		const float m_MaxDt;
	};

	template <typename Func>
	class CPUTimer
	{
	public:
		CPUTimer(const char* _name, Func&& _fnc) :
			m_Name(_name), m_Func(_fnc), m_Stopped(false), m_LastTime(Timer::Now())
		{}
		~CPUTimer()
		{
			if (!m_Stopped)
				Stop();
		}

		void Stop()
		{
			TimePoint nowTime = Timer::Now();
			float duration = Timer::Difference(nowTime, m_LastTime);
			m_LastTime = nowTime;

			m_Stopped = true;

			m_Func({ m_Name, duration });
		}

	private:
		using Time = std::chrono::high_resolution_clock;
		using TimePoint = std::chrono::time_point<Time>;

		Func m_Func;
		TimePoint m_LastTime;

		const char* m_Name;
		bool m_Stopped;
	};

	struct ProfileResult
	{
		const char* name;
		float time;
	};
}

#define CPUPROFILE_SCOPE(NAME) Radiance::CPUTimer timer##__LINE__(#NAME, [&](ProfileResult _profileResult) {m_ProfileResults.push_back(_profileResult);} )

#define CPUPROFILE_BEGIN(NAME) Radiance::CPUTimer NAME(#NAME, [&](Radiance::ProfileResult _profileResult) {m_ProfileResults.push_back(_profileResult);} )

#define CPUPROFILE_END(NAME) NAME.Stop()
