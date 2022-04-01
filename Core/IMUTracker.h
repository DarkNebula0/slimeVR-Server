#pragma once
#include "Tracker.h"
#include "TrackerWithTPS.h"
#include "TrackerWithBattery.h"
#include <qquaternion.h>

namespace VRTracker {
	class CIMUTracker: public CTracker, public CTrackerWithTPS, public CTrackerWithBattery
	{
		
	public:
		enum class ECalibrationAccuracy : uint32_t {
			Unreliable = 0x00,
			Low,
			Medium,
			High
		};
	public:
		CIMUTracker(std::string_view i_stName);
		virtual ~CIMUTracker() = default;
	private:
		void calculateLiveMagnetometerCorrection();
	public:
		virtual bool hasRotation() final { return true; }
		virtual bool position(QVector3D& i_oStore) final;
		virtual bool rotation(QQuaternion& i_oStore) final;
		virtual void resetYaw(const QQuaternion& i_oReference) final;
		virtual void tick() final;
	public:
		__inline const QQuaternion& correction() const {
			return this->m_oCorrection;
		}
	private:
		QQuaternion m_oCorrection;
		QQuaternion m_oRotMagQuaternion;
		QQuaternion m_oRotQuaternion;
		QQuaternion m_oRotAdjust;
		uint32_t m_nMagCalibrationStatus;
		bool m_bIsMagentometerCalibrated;
		bool m_bHasNewCorrectionData;
		float m_rMagnetometerAccuracy;
	private:
		static float s_rMaxMagCorrectionAccuracy;
	};
}