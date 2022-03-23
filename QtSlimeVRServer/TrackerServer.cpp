#include "TrackerServer.h"
#include "Defines.h"
#include "TrackerPacket.h"
#include "TrackerPacketHandler.h"
#include "Logger.h"

#include <QUdpSocket>

Network::TrackerServer::CServer* TrackerServerInstance = Network::TrackerServer::CServer::instance();


void Network::TrackerServer::CServer::onSuccessfulListen()
{
	// Initialize packent handler
	TrackerHandlerInstance->initialize();

	// Connect recv event
	connect(this->getSocket(), &QUdpSocket::readyRead,
		this, &Network::TrackerServer::CServer::readPendingDatagrams);

	Network::Packet::TrackerPacket::Send::SHeartBeat grHartBeat;

	this->getSocket()->writeDatagram(reinterpret_cast<char*>(&grHartBeat), grHartBeat.length(), QHostAddress::Broadcast, UDP_PORT);
}


void Network::TrackerServer::CServer::readPendingDatagrams()
{
	while (this->getSocket()->hasPendingDatagrams()) {
		QNetworkDatagram oDatagram = this->getSocket()->receiveDatagram();
		const CPacket oPacket(oDatagram.data().data(), oDatagram.data().size());

		auto pSession = this->findNetworkIp(oDatagram.senderAddress());
		if (!pSession) {
			LOGI_DEBUG("[TrackerServer] New client connected! IP: " + oDatagram.senderAddress().toString().toStdString());
			pSession = std::make_shared<CTrackerSession>(this->getSocket());
			pSession->setNetworkIDandIP(this->newNetworkId(), oDatagram.senderAddress());
			CBaseServer::addSession(pSession);
		}

		return TrackerHandlerInstance->addTask(pSession, CNetworkPacket(oPacket, true, true), false);
	}
}