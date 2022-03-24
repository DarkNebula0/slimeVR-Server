#pragma once

#include "TrackerSession.h"
#include "NetworkPacket.h"

namespace Info
{
	namespace Packet
	{
		namespace TrackerServer
		{
			void HandshakeRequest(const std::shared_ptr<CTrackerSession>& i_pSession, const CNetworkPacket& i_oPacket);
			void HeartBeatRequest(const std::shared_ptr<CTrackerSession>& i_pSession, const CNetworkPacket& i_oPacket);
			void RSSIRequest(const std::shared_ptr<CTrackerSession>& i_pSession, const CNetworkPacket& i_oPacket);
		}
	}
}