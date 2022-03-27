#pragma once
#include "TrackerSession.h"
#include <library/NetworkPacket.h>

namespace Info
{
	namespace Packet
	{
		namespace TrackerServer
		{
			void SendHeartBeat(const std::shared_ptr<CTrackerSession>& i_pSocket);
			void SendHandshake(const std::shared_ptr<CTrackerSession>& i_pSocket);
		}
	}
}