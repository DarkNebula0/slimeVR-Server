#pragma once

#include "Tracker.h"
#include "TrackerWithTPS.h"
#include <qquaternion.h>
#include <qvector3d.h>
#include <string>

namespace VRTracker {
	class CComputedTracker: public CTracker, public CTrackerWithTPS
	{
	public:
		CComputedTracker(uint32_t i_nId, const std::string_view i_stSerial, const std::string_view i_stName, bool i_bHasRotation, bool i_bHasPosition);
		CComputedTracker(uint32_t i_nId, const std::string_view i_stName, bool i_bHasRotation, bool i_bHasPosition);
		~CComputedTracker() = default;
	public:
		virtual bool position(QVector3D& i_oStore) final;
		virtual bool rotation(QQuaternion& i_oStore) final;
		virtual bool userEditable() final  { return false; };
		virtual bool isComputed() final { return false; };
	public:
		__inline const std::string_view serial() {
			return this->m_stSerial;
		}
		__inline const std::string_view descriptiveName() {
			return this->name();
		}
	private:
		QVector3D m_oPosition;
		QQuaternion m_oRotation;
		std::string m_stSerial;
		bool m_bHasRotation;
		bool m_bHasPosition;
	};
}