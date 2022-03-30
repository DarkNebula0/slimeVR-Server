#pragma once

#include <library/Timer.h>

namespace VRTracker {
	class CTrackerWithTPS {
	public:
		CTrackerWithTPS() { m_oTimer.start(); };
		virtual ~CTrackerWithTPS() = default;
	public:
		virtual double tps() {
			return this->m_oTimer.elapsed() / 1000.0f;
		}
		__inline void dataTick() {
			this->m_oTimer.reset();
		}
	private:
		CTimer m_oTimer;
	};
}