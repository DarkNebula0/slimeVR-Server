#include "TrackerServer.h"
#include "Defines.h"
#include "TrackerPacket.h"
#include "TrackerPacketHandler.h"
#include <library/Logger.h>
#include "InfoSend.h"

#include <QUdpSocket>

Network::TrackerServer::CServer* TrackerServerInstance = Network::TrackerServer::CServer::instance();


void Network::TrackerServer::CServer::onSuccessfulListen()
{
	// Initialize packent handler
	TrackerHandlerInstance->initialize();

	// Connect recv event
	connect(this->getSocket(), &QUdpSocket::readyRead,
		this, &Network::TrackerServer::CServer::readPendingDatagrams);

}

void Network::TrackerServer::CServer::readPendingDatagrams()
{
	while (this->getSocket()->hasPendingDatagrams()) {
		QNetworkDatagram oDatagram = this->getSocket()->receiveDatagram();
		
		auto pSession = this->findNetworkIp(oDatagram.senderAddress());
		if (!pSession) {
			LOGI_DEBUG("[TrackerServer] New client connected! IP: " + oDatagram.senderAddress().toString().toStdString());
			pSession = std::make_shared<CTrackerSession>(this->getSocket());
			pSession->setNetworkIDandIP(this->newNetworkId(), oDatagram.senderAddress());
			CBaseServer::addSession(pSession);
		}

		return TrackerHandlerInstance->addTask(pSession, CNetworkPacket(oDatagram.data().data(), oDatagram.data().size(), true, true), false);
	}
}

void Network::TrackerServer::CServer::checkDisconnectedClients()
{
	if (connectionCount() != 0) {
		MutexVectorLockGuard(this->m_apSessions);
		for (auto pSession : this->m_apSessions)
		{
			if (pSession->lastHartbeatState() && !pSession->isClosed()) {
				// The tracker is most likely not available close session
				pSession->setClosed();
				MutexVectorLockGuard(this->m_apDisconnectedClients);
				this->m_apDisconnectedClients.push_back(pSession);
				continue;
			}

			if (pSession->keepAliveState() && pSession->tracker().isReady()) {
				Info::Packet::TrackerServer::SendHeartBeat(pSession);
				pSession->restartKeepAliveTimer();
			}
		}
	}
}

void Network::TrackerServer::CServer::handleDisconnectedClients()
{
	if (this->m_apDisconnectedClients.size() != 0)
	{
		MutexVectorLockGuard(this->m_apDisconnectedClients);
		for (auto pSession : this->m_apDisconnectedClients)
		{
			MutexVectorLockGuard(this->m_apSessions);
			pSession->close();
		}

		this->m_apDisconnectedClients.clear();
	}
}