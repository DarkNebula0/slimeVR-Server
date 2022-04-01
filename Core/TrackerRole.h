#pragma once
#include "DeviceType.h"
#include <string>
#include <map>

namespace VRTracker {
	enum class ETrackerRole {
		None = 0x00,
		Waist,
		LeftFoot,
		RightFoot,
		Chest,
		LeftKnee,
		RightKnee,
		LeftElbow,
		RightElbow,
		LeftShoulder,
		RightShoulder,
		LeftHand,
		RightHand,
		LeftController,
		RightController,
		Head,
		Neck,
		Camera,
		Keyboard,
		Hmd,
		Beacon,
		GenericController,
	};

	class CTrackerRole
	{
	public:
		CTrackerRole(ETrackerRole i_eRole, EDeviceType i_eType, const std::string_view i_stRoleHint, const std::string_view i_stViveRole)
			: m_eRole(i_eRole), m_eType(i_eType), m_stRoleHint(i_stRoleHint), m_stViveRole(i_stViveRole) {}
		CTrackerRole(): m_eRole(ETrackerRole::None), m_eType(EDeviceType::None) {};
		virtual ~CTrackerRole() = default;
	public:
		__inline const ETrackerRole role()  const {
			return this->m_eRole;
		}
		__inline const EDeviceType deviceType() const {
			return this->m_eType;
		}
		__inline const std::string_view roleHint() const {
			return this->m_stRoleHint;
		}
		__inline const std::string_view viveRole() const {
			return this->m_stViveRole;
		}
	private:
		ETrackerRole m_eRole;
		EDeviceType m_eType;
		std::string m_stRoleHint;
		std::string m_stViveRole;
	};

	static std::map<ETrackerRole, CTrackerRole> s_aoTrackerRole = {
		{ETrackerRole::None, CTrackerRole(ETrackerRole::None, EDeviceType::None, "", "")},
		{ETrackerRole::Waist, CTrackerRole(ETrackerRole::Waist, EDeviceType::Tracker, "vive_tracker_waist", "TrackerRole_Waist")},
		{ETrackerRole::LeftFoot, CTrackerRole(ETrackerRole::LeftFoot, EDeviceType::Tracker, "vive_tracker_left_foot", "TrackerRole_LeftFoot")},
		{ETrackerRole::RightFoot, CTrackerRole(ETrackerRole::RightFoot, EDeviceType::Tracker, "vive_tracker_right_foot", "TrackerRole_RightFoot")},
		{ETrackerRole::Chest, CTrackerRole(ETrackerRole::Chest, EDeviceType::Tracker, "vive_tracker_chest", "TrackerRole_Chest")},
		{ETrackerRole::LeftKnee, CTrackerRole(ETrackerRole::LeftKnee, EDeviceType::Tracker, "vive_tracker_left_knee", "TrackerRole_LeftKnee")},
		{ETrackerRole::RightKnee, CTrackerRole(ETrackerRole::RightKnee, EDeviceType::Tracker, "vive_tracker_right_knee", "TrackerRole_RightKnee")},
		{ETrackerRole::LeftElbow, CTrackerRole(ETrackerRole::LeftElbow, EDeviceType::Tracker, "vive_tracker_left_elbow", "TrackerRole_LeftElbow")},
		{ETrackerRole::RightElbow, CTrackerRole(ETrackerRole::RightElbow, EDeviceType::Tracker, "vive_tracker_right_elbow", "TrackerRole_RightElbow")},
		{ETrackerRole::LeftShoulder, CTrackerRole(ETrackerRole::LeftShoulder, EDeviceType::Tracker, "vive_tracker_left_shoulder", "TrackerRole_LeftShoulder")},
		{ETrackerRole::RightShoulder, CTrackerRole(ETrackerRole::RightShoulder, EDeviceType::Tracker, "vive_tracker_right_shoulder", "TrackerRole_RightShoulder")},
		{ETrackerRole::LeftHand, CTrackerRole(ETrackerRole::LeftHand, EDeviceType::Tracker, "vive_tracker_handed", "TrackerRole_Handed")},
		{ETrackerRole::RightHand, CTrackerRole(ETrackerRole::RightHand, EDeviceType::Tracker, "vive_tracker_handed", "TrackerRole_Handed")},
		{ETrackerRole::LeftController, CTrackerRole(ETrackerRole::LeftController, EDeviceType::Controller, "vive_tracker_handed", "TrackerRole_Handed")},
		{ETrackerRole::RightController, CTrackerRole(ETrackerRole::RightController, EDeviceType::Controller, "vive_tracker_handed", "TrackerRole_Handed")},
		{ETrackerRole::Head, CTrackerRole(ETrackerRole::Head, EDeviceType::Tracker, "", "")},
		{ETrackerRole::Neck, CTrackerRole(ETrackerRole::Neck, EDeviceType::Tracker, "", "")},
		{ETrackerRole::Camera, CTrackerRole(ETrackerRole::Camera, EDeviceType::Tracker, "vive_tracker_camera", "TrackerRole_Camera")},
		{ETrackerRole::Keyboard, CTrackerRole(ETrackerRole::Keyboard, EDeviceType::Tracker, "vive_tracker_keyboard", "TrackerRole_Keyboard")},
		{ETrackerRole::Hmd, CTrackerRole(ETrackerRole::Hmd, EDeviceType::Hmd, "HMD", "")},
		{ETrackerRole::Beacon, CTrackerRole(ETrackerRole::Beacon, EDeviceType::TrackingReference, "", "")},
		{ETrackerRole::GenericController, CTrackerRole(ETrackerRole::GenericController, EDeviceType::Controller, "vive_tracker_handed", "TrackerRole_Handed")},
	};
}