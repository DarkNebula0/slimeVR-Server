#pragma once

#include "TrackerSession.h"
#include <library/NetworkPacket.h>

namespace Info
{
	namespace Packet
	{
		namespace TrackerServer
		{
			void HandshakeRequest(const std::shared_ptr<CTrackerSession>& i_pSession, const CNetworkPacket& i_oPacket);
			void HeartBeatRequest(const std::shared_ptr<CTrackerSession>& i_pSession, const CNetworkPacket& i_oPacket);
			void RSSIRequest(const std::shared_ptr<CTrackerSession>& i_pSession, const CNetworkPacket& i_oPacket);
			void SensorStateRequest(const std::shared_ptr<CTrackerSession>& i_pSession, const CNetworkPacket& i_oPacket);
		}
	}
}