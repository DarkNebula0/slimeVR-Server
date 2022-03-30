#include "ComputedHumanPoseTracker.h"


VRTracker::CComputedHumanPoseTracker::CComputedHumanPoseTracker(uint32_t i_nId, const std::string_view i_stName, ETrackerPosition i_ePosition)
	: CComputedTracker(i_nId, std::string("human://").append(i_stName), true, true)
{}

VRTracker::CComputedHumanPoseTracker::CComputedHumanPoseTracker(const std::string_view i_stName, ETrackerPosition i_ePosition)
	: CComputedHumanPoseTracker(CTracker::getNextId(), i_stName, i_ePosition)
{}
