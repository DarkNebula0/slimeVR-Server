#pragma once
#include "Timer.h"
#include "Defines.h"
#include "NetworkPacket.h"
#include "NetworkId.h"
#include "Tracker.h"

#include <memory>
#include <QUdpSocket>

namespace Network
{

	namespace TrackerServer
	{
		class CSession : public IId, public std::enable_shared_from_this<CSession>
		{
		public:
			CSession(QUdpSocket *i_pSocket): m_pSocket(i_pSocket) { m_oKeepAliveTimer.start(); };
			virtual ~CSession() = default;
		private:
			CTimer m_oKeepAliveTimer;
			QUdpSocket* m_pSocket;
			CTracker m_oTracker;
		public:
			void close();
			void send(const char* i_pBuffer, size_t i_nSize);
		public:
			_inline bool keepAliveState() const { return this->m_oKeepAliveTimer.hasExpired(KEEP_ALIVE_TIMEOUT); }
			_inline CTracker &tracker()  { return this->m_oTracker; }
		public:
			_inline void restartTimer() { this->m_oKeepAliveTimer.restart(); }
			_inline void setNetworkIDandIP(const uint64_t i_nNetworkID, const QHostAddress i_oNetworkIP) { IId::setID(i_nNetworkID); IId::setIP(i_oNetworkIP);
			}
		};
	}

}

typedef Network::TrackerServer::CSession CTrackerSession;
