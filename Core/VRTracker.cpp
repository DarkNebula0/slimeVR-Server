#include "VRTracker.h"


VRTracker::CVRTracker::CVRTracker(uint32_t i_nId, const std::string_view i_stSerial, const std::string_view i_stName, bool i_bHasRotation, bool i_bHasPosition)
	: CComputedTracker(i_nId, i_stSerial, i_stName, i_bHasRotation, i_bHasPosition)
{
}

VRTracker::CVRTracker::CVRTracker(uint32_t i_nId, const std::string_view i_stName, bool i_bHasRotation, bool i_bHasPosition)
	: CVRTracker(i_nId, i_stName, i_stName, i_bHasRotation, i_bHasPosition)
{
}

VRTracker::CVRTracker::~CVRTracker()
{}