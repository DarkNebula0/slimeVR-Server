#pragma once

#include "TrackerRole.h"

namespace VRTracker {
	class CShareableTracker {
	public:
		CShareableTracker(): m_pRole(&s_aoTrackerRole[ETrackerRole::None]) {};
		virtual ~CShareableTracker() = default;
	public:
		 __inline CTrackerRole *trackerRole() {
			 return m_pRole;
		}
	protected:
		__inline void setRole(ETrackerRole i_eRole) {
			 this->m_pRole = &s_aoTrackerRole[i_eRole];
		 }
	private:
		CTrackerRole *m_pRole;
	};
}