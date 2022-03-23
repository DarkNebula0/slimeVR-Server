#pragma once
#include "Timer.h"
#include "Defines.h"
#include "NetworkPacket.h"
#include "NetworkId.h"

#include <memory>
#include <QUdpSocket>

namespace Network
{

	namespace TrackerServer
	{
		class CSession : public IId, public std::enable_shared_from_this<CSession>
		{
		public:
			CSession(QUdpSocket *i_pSocket): pSocket(i_pSocket) { m_oKeepAliveTimer.start(); };
			virtual ~CSession() = default;
		private:
			CTimer m_oKeepAliveTimer;
			QUdpSocket* pSocket;
		public:
			void close();
			_inline bool keepAliveState() const { return this->m_oKeepAliveTimer.hasExpired(KEEP_ALIVE_TIMEOUT); }
		public:
			_inline void restartTimer() { this->m_oKeepAliveTimer.restart(); }
			_inline void setNetworkIDandIP(const uint64_t i_nNetworkID, const QHostAddress i_oNetworkIP) { IId::setID(i_nNetworkID); IId::setIP(i_oNetworkIP);
			}
		};
	}

}

typedef Network::TrackerServer::CSession CTrackerSession;
