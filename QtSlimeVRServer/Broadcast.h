#pragma once

#include "TrackerSession.h"
#include <library/NetworkPacket.h>

namespace Broadcast
{
	namespace Packet
	{
		namespace TrackerServer
		{
			void PairingRequest(const std::shared_ptr<CTrackerSession>& i_pSession, const CNetworkPacket& i_oPacket);
		}
	}
}