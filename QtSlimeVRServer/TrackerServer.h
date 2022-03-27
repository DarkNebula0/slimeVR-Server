#pragma once
#include "NetworkId.h"
#include "BaseServer.h"
#include "TrackerSession.h"
#include <library/Singleton.h>
#include <library/MutexVector.h>
#include <library/NetworkPacket.h>
#include <qobject.h>

namespace Network
{
	namespace TrackerServer
	{
		class CServer : public CBaseServer<CTrackerSession>, public IIdHandler<CTrackerSession>, public CSingleton<CServer>, public QObject
		{
			friend class CSingleton<CServer>;
		private:
			CServer(): IIdHandler(this), QObject(nullptr) { m_oStartTimer.start(); };
			virtual ~CServer() = default;
		private:
			CTimer m_oStartTimer;
			CMutexVector<std::shared_ptr<CTrackerSession>> m_apDisconnectedClients;
		private:
			void readPendingDatagrams();
		private:
			void onSuccessfulListen() final;
		public:
			_inline uint startTime() const { return static_cast<uint>(m_oStartTimer.elapsed()); }
		public:
			void checkDisconnectedClients();
			void handleDisconnectedClients();
		};
	}
}

extern Network::TrackerServer::CServer* TrackerServerInstance;