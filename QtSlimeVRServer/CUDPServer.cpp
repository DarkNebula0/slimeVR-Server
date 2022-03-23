#include "CUDPServer.h"
#include "Defines.h"
#include <QNetworkDatagram>

CUDPServer::CUDPServer(QObject *parent)
	: QObject(parent), m_pUdpSocket(new QUdpSocket(this))
{
	// TODO: extract port
	this->m_pUdpSocket->bind(QHostAddress::LocalHost, UDP_PORT);

    connect(this->m_pUdpSocket, &QUdpSocket::readyRead,
        this, &CUDPServer::readPendingDatagrams);
}

CUDPServer::~CUDPServer()
{
}


void CUDPServer::readPendingDatagrams()
{
    while (this->m_pUdpSocket->hasPendingDatagrams()) {
        QNetworkDatagram oDatagram = this->m_pUdpSocket->receiveDatagram();
    }
}