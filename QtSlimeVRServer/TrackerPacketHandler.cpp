#include "TrackerPacketHandler.h"
#include "Defines.h"

#define AddOperation() (this->addPacketOperation(grOperation))

Network::Packet::TrackerServer::CHandler* TrackerHandlerInstance = Network::Packet::TrackerServer::CHandler::instance();

void Network::Packet::TrackerServer::CHandler::initialize()
{
	CBaseHandler::createPool(UDP_SERVER_WORKER_COUNT);
	LOGI("[TrackerServer] Packet initialized");
}