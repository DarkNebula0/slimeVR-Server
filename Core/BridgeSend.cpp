#include "BridgeSend.h"
#include "ProtobufMessages.pb.h"
#include "Bridge.h"

void VRDriver::BridgeSend::sendTrackerUpdate(int32_t i_nTrackerId, const double& i_dRotX, const double& i_dRotY, const double& i_dRotZ, double& i_dRotW, bool i_bSendPos, double i_dX, double i_dY, double i_dZ)
{
	messages::ProtobufMessage oMsg;
	messages::Position *pPos = oMsg.mutable_position();
	
	if (i_bSendPos) {
		pPos->set_x(i_dX);
		pPos->set_y(i_dY);
		pPos->set_z(i_dZ);
	}

	pPos->set_qx(i_dRotX);
	pPos->set_qy(i_dRotY);
	pPos->set_qz(i_dRotZ);
	pPos->set_qw(i_dRotW);
	pPos->set_tracker_id(i_nTrackerId);

	BridgeInstance->sendMessage(&oMsg);
}

void VRDriver::BridgeSend::sendTrackerAdded(int32_t i_nTrackerId, const std::string& i_stName, int32_t i_nTrackerRole)
{
	messages::ProtobufMessage oMsg;
	messages::TrackerAdded* pTrackerAdded = oMsg.mutable_tracker_added();

	pTrackerAdded->set_tracker_id(i_nTrackerId);
	pTrackerAdded->set_tracker_name(i_stName);
	pTrackerAdded->set_tracker_role(i_nTrackerRole);

	//BridgeInstance->sendMessage(&oMsg);
}