#include "TrackerPacketHandler.h"
#include "Defines.h"
#include "TrackerSession.h"
#include "Broadcast.h"
#include "TrackerPacket.h"
#include "Info.h"
#include "SensorData.h"


#define AddOperation() (this->addPacketOperation(grOperation))

Network::Packet::TrackerServer::CHandler* TrackerHandlerInstance = Network::Packet::TrackerServer::CHandler::instance();

void Network::Packet::TrackerServer::CHandler::initialize()
{
	CBaseHandler::createPool(UDP_SERVER_WORKER_COUNT);

	SOperation<CTrackerSession> grOperation;

	// Broadcast
	grOperation.nID = TrackerPacket::Receive::EID::Pairing;
	grOperation.fnFunction = &Broadcast::Packet::TrackerServer::PairingRequest;
	AddOperation();

	// Info
	grOperation.nID = TrackerPacket::Receive::EID::HeartBeat;
	grOperation.fnFunction = &Info::Packet::TrackerServer::HeartBeatRequest;
	AddOperation();

	grOperation.nID = TrackerPacket::Receive::EID::Handshake;
	grOperation.fnFunction = &Info::Packet::TrackerServer::HandshakeRequest;
	AddOperation();

	grOperation.nID = TrackerPacket::Receive::EID::RSSI;
	grOperation.fnFunction = &Info::Packet::TrackerServer::RSSIRequest;
	AddOperation();

	grOperation.nID = TrackerPacket::Receive::EID::SensorState;
	grOperation.fnFunction = &Info::Packet::TrackerServer::SensorStateRequest;
	AddOperation();

	// SensorData
	grOperation.nID = TrackerPacket::Receive::EID::RotationData;
	grOperation.fnFunction = &SensorData::Packet::TrackerServer::RotationDataRequest;
	AddOperation();

	LOGI("[TrackerServer] Packet initialized");
}