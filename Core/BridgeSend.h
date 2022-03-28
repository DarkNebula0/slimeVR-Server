#pragma once

#include <string>
#include <cstdint>

namespace VRDriver
{
	namespace BridgeSend
	{
		void sendTrackerUpdate(int32_t i_nTrackerId, const double& i_dRotX, const double& i_dRotY, const double& i_dRotZ, double& i_dRotW, bool i_bSendPos = false, double i_dX = 0.0, double i_dY = 0.0, double i_dZ = 0.0);
		void sendTrackerAdded(int32_t i_nTrackerId, const std::string& i_stName, int32_t i_nTrackerRole);
	}
}

