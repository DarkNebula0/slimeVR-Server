#include "TrackerSession.h"
#include "TrackerServer.h"
#include "Logger.h"

void Network::TrackerServer::CSession::close()
{
	LOGI_DEBUG("[TrackerServer] Socket disconnected! IP: " + this->networkIp().toString().toStdString());
	TrackerServerInstance->removeSession(this->shared_from_this());
}