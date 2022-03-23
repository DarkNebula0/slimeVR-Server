#pragma once

#include <QObject>
#include <QUdpSocket>

class CUDPServer: public QObject
{
	Q_OBJECT
public:
	CUDPServer(QObject *parent);
	~CUDPServer();
private:
	void readPendingDatagrams();
private:
	QUdpSocket *m_pUdpSocket;
};
