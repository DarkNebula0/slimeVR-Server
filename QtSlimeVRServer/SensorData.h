#pragma once

#include "TrackerSession.h"
#include "NetworkPacket.h"

namespace SensorData
{
	namespace Packet
	{
		namespace TrackerServer
		{
			void RotationDataRequest(const std::shared_ptr<CTrackerSession>& i_pSession, const CNetworkPacket& i_oPacket);
		}
	}
}