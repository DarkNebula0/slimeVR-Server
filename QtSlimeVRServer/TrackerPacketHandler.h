#pragma once
#include "BasePacketHandler.h"
#include "Singleton.h"
#include "TrackerSession.h"

namespace Network
{
	namespace Packet
	{
		namespace TrackerServer
		{
			class CHandler : public CBaseHandler<CTrackerSession>, public CSingleton<CHandler>
			{
				friend class CSingleton<CHandler>;
			private:
				CHandler() = default;
				virtual ~CHandler() = default;
			public:
				void initialize();
			};
		}
	}
}

extern Network::Packet::TrackerServer::CHandler* TrackerHandlerInstance;
