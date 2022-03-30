#pragma once

#include "ComputedTracker.h"
#include "ShareableTracker.h"

namespace VRTracker {
	class CComputedHumanPoseTracker : public CComputedTracker, public CShareableTracker
	{
	public:
		CComputedHumanPoseTracker(uint32_t i_nId, const std::string_view i_stName, ETrackerPosition i_ePosition);
		CComputedHumanPoseTracker(const std::string_view i_stName, ETrackerPosition i_ePosition);
		virtual ~CComputedHumanPoseTracker() = default;
	};
}

