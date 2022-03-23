#include "BaseServer.h"


bool Network::InitializeServer(QUdpSocket* i_pServer, const QHostAddress& i_oIp, ushort i_wPort)
{
	i_pServer->bind(QHostAddress::Any, UDP_PORT);
	const Network::EError eError = i_pServer->start(i_sIp, i_wPort, i_iMaxConnections);
	if (eError == Network::EError::EIPFormat)
	{
		LOGE("Network::CServer::initialize() Wrong IP Format! IP: " + i_sIp);
	}
	else if (eError == Network::EError::EWSALastError)
	{
		LOGE("Network::CServer::initialize() WSALastError! ID: " + std::to_string(WSAGetLastError()));
	}
	else
	{
		LOGI("Server successfully started!");

		i_pServer->execute(i_iMaxRecvByteBuffer);
		return true;
	}

	return false;
}
