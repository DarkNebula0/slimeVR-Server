#include "Info.h"
#include "TrackerPacket.h"
#include "Tracker.h"
#include "InfoSend.h"
#include "Logger.h"
#include "Global.h"

using namespace Network::Packet::TrackerPacket::Receive;

void Info::Packet::TrackerServer::HandshakeRequest(const std::shared_ptr<CTrackerSession>& i_pSession, const CNetworkPacket& i_oPacket)
{
	CheckPacket(i_oPacket, SHandshake);
	const SHandshake *p = reinterpret_cast<const SHandshake*>(i_oPacket.buffer());

	// Set basic tracker info
	auto &trackerInfo = i_pSession->tracker().info();
	trackerInfo.eIMU = static_cast<CTracker::EImu>(p->nImu);
	trackerInfo.chMAC =p->achMac;

	LOGI_DEBUG("[HandshakeRequest] New Tracker IMU-Type: " + std::to_string(trackerInfo.eIMU));

	SendHandshake(i_pSession);
}

void Info::Packet::TrackerServer::HeartBeatRequest(const std::shared_ptr<CTrackerSession>& i_pSession, const CNetworkPacket& i_oPacket)
{
	i_pSession->restartTimer();
}