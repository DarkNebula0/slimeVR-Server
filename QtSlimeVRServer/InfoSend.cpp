#include "InfoSend.h"
#include "Defines.h"
#include "TrackerPacket.h"

using namespace Network::Packet::TrackerPacket::Send;

void Info::Packet::TrackerServer::SendHeartBeat(const std::shared_ptr<CTrackerSession>& i_pSocket)
{
	SHeartBeat grHeartBeat;
	SendStruct(grHeartBeat, i_pSocket);
}

void Info::Packet::TrackerServer::SendHandshake(const std::shared_ptr<CTrackerSession>& i_pSocket)
{
	SHandshake grHandshake;
	SendStruct(grHandshake, i_pSocket);
}
