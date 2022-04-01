#pragma once
#include "ComputedTracker.h"

namespace VRTracker {
	class CVRTracker: public CComputedTracker
	{
	public:
		CVRTracker(uint32_t i_nId, const std::string_view i_stSerial, const std::string_view i_stName, bool i_bHasRotation, bool i_bHasPosition);
		CVRTracker(uint32_t i_nId, const std::string_view i_stName, bool i_bHasRotation, bool i_bHasPosition);
		virtual ~CVRTracker();
	public:
		virtual bool isComputed() final { return false; };
	};
}