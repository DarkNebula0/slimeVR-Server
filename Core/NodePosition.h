#pragma once

namespace VRProcessor {
	enum class ENodePosition {
		None = 0x00,
		Hmd,
		Head,
		Neck,
		Chest,
		ChestTracker,
		Waist,
		Hip,
		WaistTracker,
		LeftHip,
		LeftKnee,
		LeftKneeTracker,
		LeftAnkle,
		LeftFoot,
		LeftFootTracker,
		RightHip,
		RightKnee,
		RightKneeTracker,
		RightAnkle,
		RightFoot,
		RightFootTracker,
		LeftHand,
		RightHand,
		LeftWrist,
		RightWrist,
		LeftElbow,
		RightElbow,
		LeftElbowTracker,
		RightElbowTracker,
	};
}