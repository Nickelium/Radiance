#include "pch.h"
#include "Time.h"

namespace Radiance
{
	Timer::Timer()
		: m_MaxDt(0.1f), m_Dt(0.0f)
	{
		Start();
	}

	void Timer::Start()
	{
		m_Start = Timer::Now();
		m_Current = m_Start = m_Last;
	}

	void Timer::Update()
	{
		m_Current = Timer::Now();
		m_Dt = std::min(m_MaxDt, Timer::Difference(m_Current, m_Last));
		m_Last = m_Current;
	}

	float Timer::GetDelta() const
	{
		return m_Dt;
	}

	float Timer::GetTotal() const
	{
		return Difference(m_Current, m_Start);
	}

	DataTime Timer::GetTimeStep() const
	{
		return DataTime{ GetDelta(), GetTotal() };
	}
}