#pragma once
#include "TrackerStatus.h"
#include "TrackerPosition.h"

#include <atomic>
#include <qvector3d.h>
#include <qquaternion.h>
#include <string>

namespace VRTracker {
	class CTracker {
	public:
		CTracker(uint32_t i_nId, const std::string_view i_stName);
		CTracker();
		virtual ~CTracker() = default;
	private:
		static std::atomic<uint32_t> s_nTrackerId;
	public:
		static int32_t getNextId() {
			return s_nTrackerId++;
		}
	public:
		virtual bool position(QVector3D& i_oStore) { return false; }
		virtual bool rotation(QQuaternion& i_oStore) { return false; }
		virtual void resetFull(const QQuaternion& i_oReference) {}
		virtual void resetYaw(const QQuaternion& i_oReference) {}
		virtual void tick() {}
		virtual bool userEditable() { return false; }
		virtual bool hasRotation() { return false; }
		virtual bool hasPosition() { return false; }
		virtual bool isComputed() { return false; }

		__inline const std::string_view name() { return this->m_stName; }
		__inline const ETrackerStatus status() { return this->m_eStatus; }
		__inline const float confidenceLevel() { return this->m_rConfidenceLevel; }
		__inline const CTrackerPosition* bodyPosition() { return this->m_pTrackerPos; }
		__inline const uint32_t id() { return this->m_nId; }

		__inline void setStatus(ETrackerStatus i_eStatus) { 
			this->m_eStatus = i_eStatus;
		}
		__inline void setBodyPosition(ETrackerPosition i_ePosition) {
			this->m_pTrackerPos = &s_aoTrackerPosition[i_ePosition];
		}
	protected:
		__inline void setName(const std::string_view i_stName) {
			this->m_stName = i_stName;
		}
		__inline void setConfidenceLevel(float i_rConfidenceLevel) {
			this->m_rConfidenceLevel = i_rConfidenceLevel;
		}
	
		__inline void setId(uint32_t i_nId) {
			this->m_nId = i_nId;
		}
	protected:
		QVector3D m_oPosition;
		QQuaternion m_oRotation;
	private:
		std::string m_stName;
		ETrackerStatus m_eStatus;
		float m_rConfidenceLevel;
		CTrackerPosition *m_pTrackerPos;
		uint32_t m_nId;
	};

}
