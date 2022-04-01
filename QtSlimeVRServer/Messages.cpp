#include "Messages.h"
#include "../Core/ProtobufMessages.pb.h"
#include "../Core/HumanPoseProcessor.h"
#include "../Core/VRTracker.h"
#include <library/Logger.h>

void VRDriver::Messages::Position(const messages::ProtobufMessage* i_pMessage)
{
	const auto& oPosition = i_pMessage->position();
	auto pTracker = HumanPoseProcessorInstance->getVRTrackerById(oPosition.tracker_id());
	if (!pTracker) {
		return;
	}
	
	if (oPosition.has_x()) {
		pTracker->setPosition(QVector3D(oPosition.x(), oPosition.y(), oPosition.z()));
	}
	
	pTracker->setRotation(QQuaternion(oPosition.qw(), oPosition.qx(), oPosition.qy(), oPosition.qz()));
	pTracker->dataTick();
}

void VRDriver::Messages::UserAction(const messages::ProtobufMessage* i_pMessage)
{
	LOGI("UserAction");
}

void VRDriver::Messages::TrackerAdded(const messages::ProtobufMessage* i_pMessage)
{
	const auto &oTrackerAdded = i_pMessage->tracker_added();

	auto pTracker = std::make_shared<VRTracker::CVRTracker>(oTrackerAdded.tracker_id(), oTrackerAdded.tracker_serial(), oTrackerAdded.tracker_name(), true, true);
	auto eRole = static_cast<VRTracker::ETrackerRole>(oTrackerAdded.tracker_role());
	auto ePosition = VRTracker::getTrackerPositionFromRole(eRole);

	pTracker->setBodyPosition(ePosition);
	HumanPoseProcessorInstance->addVRTracker(ePosition, pTracker);

	LOGI_DEBUG("{VRDriver::Messages::TrackerAdded} Add new tracker id: " + std::to_string(oTrackerAdded.tracker_id()) + " Role: " + std::string(VRTracker::s_aoTrackerRole[eRole].roleHint()));
}

void VRDriver::Messages::TrackerStatus(const messages::ProtobufMessage* i_pMessage)
{
	const auto& oTrackerStatus = i_pMessage->tracker_status();

	auto pTracker = HumanPoseProcessorInstance->getVRTrackerById(oTrackerStatus.tracker_id());
	if (!pTracker) {
		return;
	}

	pTracker->setStatus(static_cast<VRTracker::ETrackerStatus>(oTrackerStatus.status()));

	LOGI_DEBUG("{VRDriver::Messages::TrackerStatus} Add new tracker id: " + std::to_string(oTrackerStatus.tracker_id()) + " Status: " + std::to_string(oTrackerStatus.status()));
}
