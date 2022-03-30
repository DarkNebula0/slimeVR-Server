#pragma once

#include <library/Timer.h>

namespace VRTracker {
	class CTrackerWithBattery {
	public:
		CTrackerWithBattery() : m_rLevel(0.0f), m_rVoltage(0.0f) { };
		virtual ~CTrackerWithBattery() = default;
	public:
		__inline const float betteryLevel() {
			return this->m_rLevel;
		}
		__inline const float betteryVoltage() {
			this->m_rVoltage;
		}
	public:
		__inline void setBetteryLevel(float i_rLevel) {
			this->m_rLevel = i_rLevel;
		}
		__inline void setBetteryVoltage(float i_rVoltage) {
			this->m_rVoltage = i_rVoltage;
		}
	private:
		float m_rLevel;
		float m_rVoltage;
	};
}