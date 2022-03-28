#include "Messages.h"
#include "../Core/ProtobufMessages.pb.h"
#include <library/Logger.h>

void VRDriver::Messages::Position(const messages::ProtobufMessage* i_pMessage)
{
	LOGI("Position");
}

void VRDriver::Messages::UserAction(const messages::ProtobufMessage* i_pMessage)
{
	LOGI("UserAction");
}

void VRDriver::Messages::TrackerAdded(const messages::ProtobufMessage* i_pMessage)
{
	LOGI("TrackerAdded");
}

void VRDriver::Messages::TrackerStatus(const messages::ProtobufMessage* i_pMessage)
{
	LOGI("TrackerStatus");
}
