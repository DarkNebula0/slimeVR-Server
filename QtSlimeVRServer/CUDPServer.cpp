#include "CUDPServer.h"
#include "Defines.h"
#include <QNetworkDatagram>
#include "TrackerPacket.h"
#include "Logger.h"

CUDPServer::CUDPServer(QObject *parent)
	: QObject(parent), m_pUdpSocket(new QUdpSocket(this))
{
	// TODO: extract port
	this->m_pUdpSocket->bind(QHostAddress::Any, UDP_PORT);

    Network::Packet::TrackerPacket::Send::SHeartBeat grHartBeat;

    connect(this->m_pUdpSocket, &QUdpSocket::readyRead,
        this, &CUDPServer::readPendingDatagrams);

        this->m_pUdpSocket->writeDatagram(reinterpret_cast<char*>(&grHartBeat), grHartBeat.length(), QHostAddress::Broadcast, UDP_PORT);
   
}

CUDPServer::~CUDPServer()
{
}


void CUDPServer::readPendingDatagrams()
{
    while (this->m_pUdpSocket->hasPendingDatagrams()) {
        QNetworkDatagram oDatagram = this->m_pUdpSocket->receiveDatagram();
        qDebug() << oDatagram.data();
    }
}