#include "TrackerSession.h"
#include "TrackerServer.h"
#include "Defines.h"
#include "Logger.h"

void Network::TrackerServer::CSession::close()
{
	LOGI_DEBUG("[TrackerServer] Socket disconnected! IP: " + this->networkIp().toString().toStdString());
	TrackerServerInstance->removeSession(this->shared_from_this());
}

void Network::TrackerServer::CSession::send(const char* i_pBuffer, size_t i_nSize)
{
	m_pSocket->writeDatagram(i_pBuffer, i_nSize, this->networkIp(), UDP_PORT);
}
