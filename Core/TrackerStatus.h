#pragma once

namespace VRTracker {
	enum class ETrackerStatus {
		Disconnected = 0x00,
		Ok,
		Busy,
		Error,
		Occluded
	};
}