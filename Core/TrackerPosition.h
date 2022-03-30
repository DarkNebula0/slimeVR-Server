#pragma once
#include "TrackerStatus.h"
#include "TrackerRole.h"
#include <string>
#include <map>

namespace VRTracker {
	enum class ETrackerPosition {
		None = 0x00,
		Hmd,
		Chest,
		Waist,
		Hip,
		LeftLeg,
		RightLeg,
		LeftAnkle,
		RightAnkle,
		LeftFoot,
		RightFoot,
		LeftController,
		RightController,
		LeftElbow,
		RightElbow
	};

	class CTrackerPosition {
	public:
		CTrackerPosition(ETrackerPosition i_ePosition, const std::string_view i_stDesignation, const CTrackerRole& i_oTrackerRole)
			: m_ePos(i_ePosition), m_stDesignation(i_stDesignation), m_oRole(i_oTrackerRole) {};
		CTrackerPosition(): m_ePos(ETrackerPosition::None) {};
		virtual ~CTrackerPosition() = default;
	public:
		__inline const ETrackerPosition position() {
			return this->m_ePos;
		}
		__inline const std::string_view designation() {
			return this->m_stDesignation;
		}
		__inline const CTrackerRole& role() {
			return this->m_oRole;
		}
	private:
		ETrackerPosition m_ePos;
		std::string m_stDesignation;
		CTrackerRole m_oRole;
	};

	static std::map<ETrackerPosition, CTrackerPosition> s_aoTrackerPosition = {
		{ETrackerPosition::None, CTrackerPosition(ETrackerPosition::None,"",s_aoTrackerRole[ETrackerRole::None])},
		{ETrackerPosition::Hmd, CTrackerPosition(ETrackerPosition::Hmd,"HMD",s_aoTrackerRole[ETrackerRole::Hmd])},
		{ETrackerPosition::Chest, CTrackerPosition(ETrackerPosition::Chest,"body:chest",s_aoTrackerRole[ETrackerRole::Chest])},
		{ETrackerPosition::Waist, CTrackerPosition(ETrackerPosition::Waist,"body:waist",s_aoTrackerRole[ETrackerRole::Waist])},
		{ETrackerPosition::Hip, CTrackerPosition(ETrackerPosition::Hip,"body:hip",s_aoTrackerRole[ETrackerRole::None])},
		{ETrackerPosition::LeftLeg, CTrackerPosition(ETrackerPosition::LeftLeg,"body:left_leg",s_aoTrackerRole[ETrackerRole::LeftKnee])},
		{ETrackerPosition::RightLeg, CTrackerPosition(ETrackerPosition::RightLeg,"body:right_leg",s_aoTrackerRole[ETrackerRole::RightKnee])},
		{ETrackerPosition::LeftAnkle, CTrackerPosition(ETrackerPosition::LeftAnkle,"body:left_ankle",s_aoTrackerRole[ETrackerRole::None])},
		{ETrackerPosition::RightAnkle, CTrackerPosition(ETrackerPosition::RightAnkle,"body:right_ankle",s_aoTrackerRole[ETrackerRole::None])},
		{ETrackerPosition::LeftFoot, CTrackerPosition(ETrackerPosition::LeftFoot,"body:left_foot",s_aoTrackerRole[ETrackerRole::LeftFoot])},
		{ETrackerPosition::RightFoot, CTrackerPosition(ETrackerPosition::RightFoot,"body:right_foot",s_aoTrackerRole[ETrackerRole::RightFoot])},
		{ETrackerPosition::LeftController, CTrackerPosition(ETrackerPosition::LeftController,"body:left_controller",s_aoTrackerRole[ETrackerRole::LeftController])},
		{ETrackerPosition::RightController, CTrackerPosition(ETrackerPosition::RightController,"body:right_controller",s_aoTrackerRole[ETrackerRole::RightController])},
		{ETrackerPosition::LeftElbow, CTrackerPosition(ETrackerPosition::LeftElbow,"body:left_elbow",s_aoTrackerRole[ETrackerRole::LeftElbow])},
		{ETrackerPosition::RightElbow, CTrackerPosition(ETrackerPosition::RightElbow,"body:right_elbow",s_aoTrackerRole[ETrackerRole::RightElbow])}
	};
}