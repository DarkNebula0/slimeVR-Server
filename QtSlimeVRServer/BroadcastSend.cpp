#include "BroadcastSend.h"
#include "TrackerPacket.h"
#include "TrackerServer.h"

using namespace Network::Packet::TrackerPacket::Send;

void Broadcast::Packet::TrackerServer::SendPairing()
{
	SPairing grPairing;
	BroadcastStruct(grPairing);
}