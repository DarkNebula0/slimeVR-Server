#pragma once
#include "Defines.h"
#include "NetworkId.h"
#include "Tracker.h"
#include "../Core/Timer.h"
#include "../Core/NetworkPacket.h"

#include <memory>
#include <QUdpSocket>

namespace Network
{

	namespace TrackerServer
	{
		class CSession : public IId, public std::enable_shared_from_this<CSession>
		{
		public:
			CSession(QUdpSocket* i_pSocket) : m_pSocket(i_pSocket), m_bIsClosed(false) { m_oKeepAliveTimer.start(); m_oLastHartbeat.start(); };
			virtual ~CSession() = default;
		private:
			CTimer m_oKeepAliveTimer;
			CTimer m_oLastHartbeat;
			QUdpSocket* m_pSocket;
			CTracker m_oTracker;
			bool m_bIsClosed;
		public:
			void close();
			void send(const char* i_pBuffer, size_t i_nSize);
		public:
			_inline bool keepAliveState() const { return this->m_oKeepAliveTimer.hasExpired(KEEP_ALIVE_TIMEOUT); }
			_inline bool lastHartbeatState() const { return this->m_oLastHartbeat.hasExpired(HEART_BEAT_TIMEOUT); }
			_inline bool isClosed() const { return this->m_bIsClosed; }
			_inline CTracker &tracker()  { return this->m_oTracker; }
			
		public:
			_inline void restartKeepAliveTimer() { this->m_oKeepAliveTimer.restart(); }
			_inline void restartHeartBeatTimer() { this->m_oLastHartbeat.restart(); }
			_inline void setNetworkIDandIP(const uint64_t i_nNetworkID, const QHostAddress i_oNetworkIP) {
				IId::setID(i_nNetworkID); IId::setIP(i_oNetworkIP);
			}
			_inline void setClosed() { this->m_bIsClosed = true; }
		};
	}

}

typedef Network::TrackerServer::CSession CTrackerSession;
